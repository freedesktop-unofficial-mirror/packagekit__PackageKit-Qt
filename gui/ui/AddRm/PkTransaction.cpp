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
#include "../Common/PkStrings.h"
#include "PkTransaction.h"

PkTransaction::PkTransaction( Transaction *trans, QString caption, QWidget *parent )
 : KDialog(parent), m_trans(trans)
{
    setupUi( mainWidget() );
    setCaption( caption );

    connect( m_trans, SIGNAL( GotPackage(Package *) ), this, SLOT( currPackage(Package *) ) );
    connect( m_trans, SIGNAL( Finished(Exit::Value, uint) ), this, SLOT( Finished(Exit::Value, uint) ) );
    connect( m_trans, SIGNAL( AllowCancel(bool) ), this, SLOT( enableButtonCancel(bool) ) );
    connect( m_trans, SIGNAL( ErrorCode(const QString&, const QString&) ), this, SLOT( ErrorCode(const QString&, const QString&) ) );
    connect( m_trans, SIGNAL( ProgressChanged(uint, uint, uint, uint) ), this, SLOT( ProgressChanged(uint, uint, uint, uint) ) );
    connect( m_trans, SIGNAL( StatusChanged(Status::Value) ), this, SLOT( StatusChanged(Status::Value) ) );
    
    // Set Cancel and custom buoton hide
    setButtons( KDialog::Cancel | KDialog::User1 );
    setButtonText( KDialog::User1, i18n("Hide") );
    setButtonToolTip( KDialog::User1, i18n("Allows you to hide the window but keeps running transaction task") );
    enableButtonCancel(false);

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
            break;
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
    currentL->setText( PkStrings::StatusChanged(v) );
}

void PkTransaction::ErrorCode(const QString &one, const QString &two)
{
    KMessageBox::detailedSorry( this, one, two, i18n("Erro PackageKit"), KMessageBox::Notify );
}

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
//     switch(status) {
//         default :
//             close();
//     }
qDebug() << "trans finished: " << status ;
    switch(status) {
        case Exit::Success :
	    qDebug() << "trans succes: ";
	    break;
	case Exit::Failed :
	    qDebug() << "trans failed: ";
            m_notifyT.start(50);
	    break;
	case Exit::Kill :
            qDebug() << "trans quit: ";
            break;
	case Exit::Unknown :
            qDebug() << "trans quit: ";
            break;
    }
}

#include "PkTransaction.moc"
