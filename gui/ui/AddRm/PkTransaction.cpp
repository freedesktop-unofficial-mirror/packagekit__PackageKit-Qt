/***************************************************************************
 *   Copyright (C) 2008 by Daniel Nicoletti   *
 *   mirttex85-pk@yahoo.com.br   *
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

#include <KLocale>
// #include <KStandardDirs>
#include <KMessageBox>

// #include <QPalette>
// #include <QColor>
// #include "PkRequirements.h"
#include "PkTransaction.h"

PkTransaction::PkTransaction( Transaction *trans, QString &caption, QWidget *parent )
 : KDialog(parent), m_trans(trans)
{
    setupUi( mainWidget() );
    setCaption( caption );
//     // Create a new daemon
//     m_daemon = new Daemon(this);
//     // Create the requirements transaction and it's model
//     m_pkClient_req = m_daemon->newTransaction();
//     m_pkg_model_req = new PkAddRmModel(this);
//     connect( m_pkClient_req, SIGNAL( GotPackage(Package *) ), m_pkg_model_req, SLOT( addPackage(Package *) ) );
//     connect( m_pkClient_req, SIGNAL( Finished(Exit::Value, uint) ), this, SLOT( reqFinished(Exit::Value, uint) ) );

//     // create the install transaction
//     m_pkClient_action = m_daemon->newTransaction();
    connect( m_trans, SIGNAL( GotPackage(Package *) ), this, SLOT( currPackage(Package *) ) );
    connect( m_trans, SIGNAL( Finished(Exit::Value, uint) ), this, SLOT( Finished(Exit::Value, uint) ) );
    connect( m_trans, SIGNAL( AllowCancel(bool) ), this, SLOT( enableButtonCancel(bool) ) );
    connect( m_trans, SIGNAL( ErrorCode(const QString&, const QString&) ), this, SLOT( ErrorCode(const QString&, const QString&) ) );

    connect( m_trans, SIGNAL( ProgressChanged(uint, uint, uint, uint) ), this, SLOT( ProgressChanged(uint, uint, uint, uint) ) );
    connect( m_trans, SIGNAL( StatusChanged(Status::Value) ), this, SLOT( StatusChanged(Status::Value) ) );
    
    // Set Cancel and custom bt hide
    setButtons( KDialog::Cancel | KDialog::User1 );
    setButtonText( KDialog::User1, i18n("Hide") );
    setButtonToolTip( KDialog::User1, i18n("Allows you to hide the window but keeps running transaction task") );
    enableButtonCancel(false);

    
//     m_pkClient_req->getDepends("~installed", pkg, true);
    m_pbTimer = new QTimer(this);
    connect(m_pbTimer, SIGNAL(timeout()), this, SLOT(updateProgress() ));
    m_pbTimer->start(5);

    // set wait msg
    currentL->setText( i18n("Please Wait..." ) );
}

void PkTransaction::updateProgress()
{
    progressBar->setValue(progressBar->value() + 1);
}

void PkTransaction::ProgressChanged(uint percentage, uint /*subpercentage*/, uint /*elapsed*/, uint /*remaining*/)
{
    m_pbTimer->stop();
    progressBar->setMaximum(100);
    progressBar->setValue(percentage);
}

void PkTransaction::currPackage(Package *p)
{
    packageL->setText( p->name() + " - " + p->version() + " (" + p->arch() + ")" );
    descriptionL->setText( p->summary() );
}

void PkTransaction::slotButtonClicked(int button)
{
    switch(button) {
        case KDialog::Cancel :
            m_trans->cancel();
            break;/*accept();*/
        case KDialog::User1 :
            close();
            break;
        default :
            KDialog::slotButtonClicked(button);
    }
}

PkTransaction::~PkTransaction()
{

}

void PkTransaction::StatusChanged(Status::Value v)
{
    switch (v) {
        case Status::Setup : 
	    currentL->setText( i18n("Waiting for service to start") );
	    break;
        case Status::Wait :
	    currentL->setText( i18n("Waiting for other tasks") );
	    break;
        case Status::Query :
	    currentL->setText( i18n("Querying") );
	    break;
        case Status::Info :
	    currentL->setText( i18n("Getting information") );
	    break;
        case Status::Remove :
	    currentL->setText( i18n("Removing") );
	    break;
        case Status::Refresh_cache :
	    currentL->setText( i18n("Refreshing software list") );
	    break;
        case Status::Download :
	    currentL->setText( i18n("Downloading") );
	    break;
        case Status::Install :
	    currentL->setText( i18n("Installing") );
	    break;
        case Status::Update :
	    currentL->setText( i18n("Updating") );
	    break;
        case Status::Cleanup :
	    currentL->setText( i18n("Cleaning Up") );
	    break;
        case Status::Obsolete :
	    currentL->setText( i18n("Obsoletiong") );
	    break;
        case Status::Dep_resolve :
	    currentL->setText( i18n("Resolving dependencies") );
	    break;
        case Status::Rollback :
	    currentL->setText( i18n("Rolling back") );
	    break;
        case Status::Commit :
	    currentL->setText( i18n("Committing changes") );
	    break;
        case Status::Request :
	    currentL->setText( i18n("Requesting data") );
	    break;
        case Status::Finished :
	    currentL->setText( i18n("Finished") );
	    break;
        case Status::Cancel :
	    currentL->setText( i18n("Cancelling") );
	    break;
        case Status::Unknown :
	    currentL->setText( i18n("Unknown state") );
	    break;
	default :
	    currentL->setText( i18n("Running task") );
	    break;
    }
}

void PkTransaction::ErrorCode(const QString &one, const QString &two)
{
    KMessageBox::detailedSorry( this, one, two, i18n("Error PackageKit"), KMessageBox::Notify );
}

// void PkTransaction::doAction()
// {
//     m_pkClient_action->installPackage(m_targetPackage);
// }

// void PkTransaction::reqFinished(Exit::Value status, uint runtime)
// {
//     switch(status) {
//         case Exit::Success :
//             if (m_pkg_model_req->rowCount( QModelIndex() ) > 0 ) {
// 	        KDialog *dialog = new KDialog( this );
//                 dialog->setCaption( "Confirm" );
//                 dialog->setButtons( KDialog::Ok | KDialog::Cancel );
// 
//                 PkRequirements *widget = new PkRequirements( i18n("The following packages must also be installed"), m_pkg_model_req, this );
//                 dialog->setMainWidget( widget );
//                 connect( dialog, SIGNAL( okClicked() ), this, SLOT( doAction() ) );
// 		connect( dialog, SIGNAL( cancelClicked() ), this, SLOT( close() ) );
// 		dialog->exec();qDebug() << "exec())) ...";
// 	    }
//             else
//                 doAction();
// 		// 	case Status::Failed :
// // 	    currentL->setText( i18n("Failed") );
// // 	    break;
// // 	case Status::Quit :
// // 	    currentL->setText( i18n("Quiting") );
// // 	    break;
// // 	case Status::Kill :
// // 	    currentL->setText( i18n("Killing") );
// // 	    break;
//     }
// }

void PkTransaction::Finished(Exit::Value status, uint /*runtime*/)
{
    switch(status) {
        default :
            close();
    }
qDebug() << "trans finished: " << status ;
//     notifyF->show();
//     QPalette teste;
//     switch(status) {
//         case Exit::Success :
// 	    notifyL->setText("Search finished in " + KGlobal::locale()->formatDuration(runtime) );
//             teste.setColor( QPalette::Normal, QPalette::Window, QColor(0,255,0,150));
//             notifyL->setPalette(teste);
//             notifyL->setAutoFillBackground(true);
//             m_notifyT.start(100);
// 	    break;
// 	case Exit::Failed :
// 	    notifyL->setText("Search Failed " + KGlobal::locale()->formatDuration(runtime) );
//             teste.setColor(QPalette::Normal, QPalette::Window, QColor(255,0,0,150));
//             notifyL->setPalette(teste);
//             notifyL->setAutoFillBackground(true);
//             m_notifyT.start(50);
// 	    break; 	
// 	case Exit::Quit : break;
// 	case Exit::Kill : break;
// 	case Exit::Unknown : break;
//     }
}

#include "PkTransaction.moc"