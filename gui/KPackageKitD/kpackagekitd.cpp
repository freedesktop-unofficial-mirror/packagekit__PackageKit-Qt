/***************************************************************************
 *   Copyright (C) 2008 by Daniel Nicoletti                                *
 *   dantti85-pk@yahoo.com.br                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "kpackagekitd.h"

#include <KGenericFactory>
#include <KStandardDirs>
#include <KConfigGroup>
#include <QDateTime>
#include <limits.h>

#define TEN_MIN 600000

K_PLUGIN_FACTORY(KPackageKitFactory, registerPlugin<KPackageKitD>(); )
K_EXPORT_PLUGIN(KPackageKitFactory("kpackagekitd"))

KPackageKitD::KPackageKitD(QObject *parent, const QList<QVariant>&)
    : KDEDModule(parent)
{
    m_qtimer = new QTimer(this);
    connect( m_qtimer, SIGNAL( timeout() ), this, SLOT( init() ) ) ;
    // Start after 10 minutes, 600000 msec
    // To keep the startup fast..
    m_qtimer->start(TEN_MIN);
}

KPackageKitD::~KPackageKitD()
{
}

void KPackageKitD::init()
{
    m_qtimer->stop();
    m_qtimer->disconnect();
    connect( m_qtimer, SIGNAL( timeout() ), this, SLOT( read() ) );

    // Create a new daemon
    m_daemon = new Daemon(this);

    uint actions = m_daemon->getActions();

    if ( !(actions & Actions::Refresh_cache) ) {
        //if the backend does not suport refreshing cache let's don't do nothing
        return;
    }

    m_pkClient_updates = m_daemon->newTransaction();
//     connect( m_pkClient_updates, SIGNAL(GotPackage(Package *)), m_pkg_model_updates, SLOT(addPackage(Package *)) );
    connect( m_pkClient_updates, SIGNAL( Finished(Exit::Value, uint)), this, SLOT( Finished(Exit::Value, uint) ) );
    
    read();
    
    //check if any changes to the file occour
    //this also prevents from reading when a checkUpdate happens
    m_confWatch = new KDirWatch(this);
    m_confWatch->addFile( KStandardDirs::locateLocal("config", "KPackageKit") );
    connect( m_confWatch, SIGNAL( dirty(const QString &) ), this, SLOT( read() ) );
    connect( m_confWatch, SIGNAL( created(const QString &) ), this, SLOT( read() ) );
    connect( m_confWatch, SIGNAL( deleted(const QString &) ), this, SLOT( read() ) );
    m_confWatch->startScan();
}

void KPackageKitD::read()
{
    KConfig config("KPackageKit");
    KConfigGroup checkUpdateGroup( &config, "CheckUpdate" );
    // default to one day, 86400 sec
    uint interval = checkUpdateGroup.readEntry( "interval", 86400 );
    if ( interval == 0 )
        return;
    uint lastCheck = checkUpdateGroup.readEntry( "lastChecked", 0 );
    uint now = QDateTime::currentDateTime().toTime_t();
    if ( interval + lastCheck < now ) {
        checkUpdates();
    }
    else
    {
        //interval - (now - lastCheck)
        //Schedule for msecs...
        //check first to see any overflow...
        if ( (interval + lastCheck - now) > 4294966 )
            m_qtimer->start( UINT_MAX );
        else
            m_qtimer->start( (interval + lastCheck - now) * 1000 );
    }
}

void KPackageKitD::write()
{
    KConfig config("KPackageKit");
    KConfigGroup checkUpdateGroup( &config, "CheckUpdate" );
    checkUpdateGroup.writeEntry( "lastChecked", QDateTime::currentDateTime().toTime_t() );
}

void KPackageKitD::Finished(Exit::Value status, uint)
{
    if ( status == Exit::Success )
        write();
    else
        // try again in 10 minutes
        m_qtimer->start(TEN_MIN);
}


void KPackageKitD::checkUpdates()
{
    if ( !m_pkClient_updates->refreshCache(true) )
        // try again in 10 minutes
	m_qtimer->start(TEN_MIN);
}
