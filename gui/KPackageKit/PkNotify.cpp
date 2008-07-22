/***************************************************************************
 *   Copyright (C) 2008 by Daniel Nicoletti   *
 *   dantti85-pk@yahoo.com.br   *
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

#include "PkNotify.h"
#include <KMessageBox>
#include <KLocale>
#include <KIcon>
#include <QSize>
#include <KConfig>
#include <KConfigGroup>

#include <KDebug>

namespace kpackagekit {

PkNotify::PkNotify( QObject *parent ) : QObject( parent )
{
//     descriptionKTB->hide();

    //initialize the model, delegate, client and  connect it's signals
//     treeView->setModel(m_pkg_model_updates = new PkAddRmModel(this));
//     treeView->setItemDelegate(pkg_delegate = new PkAddRmDelegate(this));

    // Create a new daemon
    m_daemon = new Daemon(this);

    m_pkClient_updates = m_daemon->newTransaction();
//     connect( m_pkClient_updates, SIGNAL( GotPackage(Package *) ), m_pkg_model_updates, SLOT( addPackage(Package *) ) );
//     connect( m_pkClient_updates, SIGNAL(Finished(Exit::Value, uint)), this, SLOT(Finished(Exit::Value, uint)) );
//     connect( m_pkClient_updates, SIGNAL(Files(Package *, QStringList)), this, SLOT(Files(Package *, QStringList)) );
//     connect( m_pkClient_updates, SIGNAL( Message(const QString&, const QString&) ), this, SLOT( Message(const QString&, const QString&) ) );
//     connect( m_pkClient_updates, SIGNAL( ErrorCode(const QString&, const QString&) ), this, SLOT( Message(const QString&, const QString&) ) );
//     m_pkClient_updates->getUpdates("none");
}

PkNotify::~PkNotify()
{
}

void PkNotify::displayUpdates()
{
    connect( m_pkClient_updates, SIGNAL( GotPackage(Package *) ), this, SLOT( GotPackage(Package *) ) );
    connect( m_pkClient_updates, SIGNAL( Finished(Exit::Value, uint) ), this, SLOT( UpdatesFinished(Exit::Value, uint)) );
    m_pkClient_updates->getUpdates("none");
}

void PkNotify::finishInstallingRebootReq()
{
}

void PkNotify::updatesBeingInstalled()
{
}

void PkNotify::GotPackage(Package *p)
{
    packages << p;
}

void PkNotify::UpdatesFinished(Exit::Value status, uint /*runtime*/)
{
    qDebug() << "trans getUpdates finished: " << status ;
    if (status == Exit::Success) {
	if ( packages.size() ) {
	    kDebug() << "We have updates let's show...";
	    updatesNotification = new KNotification( "ShowUpdates" );
	    // here we check if they are too many
	    // i think 5 is the maximun number to show them detailed
// 	    if ( packages.size() <= 5 ) {
// 	        QString text;
// 		text.append( i18np("<b>You have one update:", "<br>You have %1 updates:</b>", packages.size() ) );
// 		for ( int i = 0; i < packages.size(); i++) {
// 		    text.append( "<br><b>" + packages.at(i)->name() + "</b> - " + packages.at(i)->summary() );
// 		}
// 		updatesNotification->setText(text);
// 	    }
// 	    else {
	        QString text;
		text.append( i18n("<b>You have %1 updates:</b>", packages.size() ) );
		
		QHash<QString, int> info;
		
// 		
    
		/*for ( int i = 0; i < packages.size(); i++) {
		    if ( p->info() == "available" || p->info() == "installed" )
			if ( p->data() == "debian" )
			    return m_iconDeb;
			else if ( p->data() == "fedora" )
			    return m_iconRpm;
			else
			    return m_iconGeneric;
		    else if ( p->info() == "bugfix" )
			return m_iconBugFix;
		    else if ( p->info() == "security-important" )
			return m_iconImportant;
		    else if ( p->info() == "security-low" )
			return m_iconLow;
		    else if ( p->info() == "enhancement" )
			return m_iconEnhancement;
		    else if ( p->info() == "security" )
			return m_iconSecurity;
		    else if ( p->info() == "normal" )
			return m_iconNormal;
		    else
			 return m_iconGeneric;
			 
		*/    
		
		
		for ( int i = 0; i < packages.size(); i++) {
		    info[ packages.at(i)->info() ] = ++info[ packages.at(i)->info() ];
		}
		// if we have only one kind of update don't show total of updates
		if ( info ) {
		    text.append( i18n("<b>You have %1 %1 updates:</b>", packages.size() ) );
		}
		else {
		    QHashIterator<QString, int> i(hash);
		    while (i.hasNext()) {
			i.next();
			cout << i.key() << ": " << i.value() << endl;
		    }
		}
		updatesNotification->setText(text);
		kDebug() << info;
// 	    }
	    KIcon icon("security-high");
	    updatesNotification->setPixmap( icon.pixmap( QSize(128,128) ) );
	    QStringList actions( i18n("Update Now") );
	    actions << i18n("Not Now");
	    actions << i18n("Don't ask anymore");
	    updatesNotification->setActions(actions);
	    //TODO close the notifications !! memoryleak
	    updatesNotification->setFlags( KNotification::Persistent );
	    connect( updatesNotification, SIGNAL( activated(uint) ), this , SLOT( updatesActions(uint) ) );
            updatesNotification->sendEvent();
	}
    }
}

void PkNotify::updatesActions(uint action)
{
    updatesNotification->close();
    kDebug() << "update Action " << action;
    switch (action) {
	case 1:
	    break;
	case 2:
	    break;
	case 3:
	    KConfig config("KPackageKit");
	    KConfigGroup smartIconGroup( &config, "SmartIcon" );
	    smartIconGroup.writeEntry( "notifyUpdates", 0 );
            break;
    }
}


}

#include "PkNotify.moc" 
