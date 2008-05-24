/***************************************************************************
 *   Copyright (C) 2008 by Daniel Nicoletti                                *
 *   mirttex85-pk@yahoo.com.br                                             *
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

//#include "kpkckagekitd.moc"
#include <kgenericfactory.h>
#include <KStandardDirs>
#include <KConfigGroup>
#include <QDateTime>

#include <KMessageBox>

#include "kpackagekitd.h"

K_PLUGIN_FACTORY(KPackageKitFactory, registerPlugin<KPackageKit>(); )
K_EXPORT_PLUGIN(KPackageKitFactory("kpackagekitd"))

KPackageKit::KPackageKit(QObject *parent, const QList<QVariant>&)
    : KDEDModule(parent)
{
    m_qtimer = new QTimer(this);
    connect(m_qtimer, SIGNAL(timeout()), this, SLOT(init()));
    // Start after 10 minutes, 600000 msec
    // To keep the startup fast..
    m_qtimer->start(1000);
}

KPackageKit::~KPackageKit()
{
    delete m_qtimer;
    delete m_confWatch;
}

void KPackageKit::init()
{
    m_qtimer->stop();
    m_qtimer->disconnect();
    connect(m_qtimer, SIGNAL(timeout()), this, SLOT(checkUpdates()));
    read();
    //check if any changes to the file occour
    //this also prevents from reading when a checkUpdate happens
    m_confWatch = new KDirWatch(this);
    m_confWatch->addFile( KStandardDirs::locateLocal("config", "KPackageKit") );
    connect(m_confWatch, SIGNAL( dirty(const QString &) ), this, SLOT( checkUpdates() ));
    connect(m_confWatch, SIGNAL( created(const QString &) ), this, SLOT( checkUpdates() ));
    connect(m_confWatch, SIGNAL( deleted(const QString &) ), this, SLOT( checkUpdates() ));
    m_confWatch->startScan();
}

void KPackageKit::read()
{
    KConfig config("KPackageKit");
    KConfigGroup checkUpdateGroup( &config, "CheckUpdate" );
    if ( checkUpdateGroup.readEntry( "never", false ) )
        return;
    // default to one day, 86400 sec
    uint interval = checkUpdateGroup.readEntry( "interval", 86400 );
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
        if ( (now - lastCheck - interval) > 4294966 )
            m_qtimer->start( UINT_MAX );
        else
            m_qtimer->start( (now - lastCheck - interval) * 1000 );
    }
}

void KPackageKit::write()
{
    KConfig config("KPackageKit");
    KConfigGroup checkUpdateGroup( &config, "CheckUpdate" );
    checkUpdateGroup.writeEntry( "lastChecked", QDateTime::currentDateTime().toTime_t() );
}

void KPackageKit::checkUpdates()
{
    KMessageBox::questionYesNo( 0, tr("Local ") + KStandardDirs::locateLocal("config", "KPackageKit")  , "Restart?");
}
