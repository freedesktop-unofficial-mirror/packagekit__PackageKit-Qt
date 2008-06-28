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

#include <KMessageBox>
#include <KDebug>

#include "PkRequirements.h"
#include "PkTransaction.h"
#include "PkReviewChanges.h"

#define UNIVERSAL_PADDING 6

PkReviewChanges::PkReviewChanges( const QList<Package*> &packages, QWidget *parent )
 : KDialog(parent), m_waitPD(0)
{
    setupUi( mainWidget() );

    //initialize the model, delegate, client and  connect it's signals
    packageView->setItemDelegate(m_pkgDelegate = new PkDelegate(this));
    packageView->setModel(m_pkgModelMain = new PkAddRmModel(packages, this));
    connect( m_pkgModelMain, SIGNAL( changed(bool) ), this, SLOT( enableButtonApply(bool) ) );

    setCaption( "Review Changes - KPackageKit" );

    // Set Apply and Cancel buttons
    setButtons( KDialog::Apply | KDialog::Cancel );

    m_pbTimer = new QTimer(this);
    connect(m_pbTimer, SIGNAL( timeout() ), this, SLOT( updateProgress() ));

    label->setText( i18n("You selected the folowwing packages to be INSTALLED/REMOVED, press ok to proceed:") );
}

void PkReviewChanges::updateProgress()
{
    if (m_waitPD)
        m_waitPD->progressBar()->setValue( m_waitPD->progressBar()->value() + 1 );
}

PkReviewChanges::~PkReviewChanges()
{

}

void PkReviewChanges::ErrorCode(const QString &one, const QString &two)
{
    KMessageBox::detailedSorry( this, one, two, i18n("Erro PackageKit"), KMessageBox::Notify );
}

void PkReviewChanges::doAction()
{
    m_daemon = new Daemon(this);

    // check what packages are installed and marked to be removed
    for (int i = 0; i < m_pkgModelMain->packagesChanges().size(); ++i) {
        if ( m_pkgModelMain->packagesChanges().at(i)->info() == "installed" )
            m_remPackages << m_pkgModelMain->packagesChanges().takeAt(i);
    }

    // check what packages are avaliable and marked to be installed
    for (int i = 0; i < m_pkgModelMain->packagesChanges().size(); ++i) {
        if ( m_pkgModelMain->packagesChanges().at(i)->info() == "available" )
            m_addPackages << m_pkgModelMain->packagesChanges().takeAt(i);
    }

    checkTask();
}

void PkReviewChanges::checkTask()
{
    if ( !m_remPackages.isEmpty() ) {
        qDebug() << "task rm if";
        if ( m_daemon->getActions() & Actions::Remove_packages ) {
	    if ( m_daemon->getActions() & Actions::Get_requires ) {
	        m_reqDepPackages = m_remPackages;
	        // Create the requirements transaction and it's model
                m_transactionReq = m_daemon->newTransaction();
                m_pkgModelReq = new PkAddRmModel(this);
                connect( m_transactionReq, SIGNAL( GotPackage(Package *) ), m_pkgModelReq, SLOT( addUniquePackage(Package *) ) );
                connect( m_transactionReq, SIGNAL( Finished(Exit::Value, uint) ), this, SLOT( reqFinished(Exit::Value, uint) ) );
		// Create a KProgressDialog to don't upset the user
		m_waitPD = new KProgressDialog(this, i18n("Wait - KPackageKit"), i18n("Checking required packages") );
		m_waitPD->progressBar()->setMinimum(0);
		m_waitPD->progressBar()->setMaximum(0);
		m_waitPD->setAutoClose(false);
		m_waitPD->setModal(true);
		m_pbTimer->start(5);
		m_waitPD->show();
		m_transactionReq->getRequires("installed", m_reqDepPackages.takeFirst(), true);
	    }
        }
	else
	    KMessageBox::error( this, i18n("Sorry, your backend does not support removing packages"), i18n("Erro KPackageKit") );
    }
    else if ( !m_addPackages.isEmpty() ) {
        qDebug() << "task add else";
        if ( m_daemon->getActions() & Actions::Install_packages ) {
	    if ( m_daemon->getActions() & Actions::Get_depends ) {
	        m_reqDepPackages = m_addPackages;
		// Create the depends transaction and it's model
                m_transactionDep = m_daemon->newTransaction();
                m_pkgModelDep = new PkAddRmModel(this);
                connect( m_transactionDep, SIGNAL( GotPackage(Package *) ), m_pkgModelDep, SLOT( addUniquePackage(Package *) ) );
                connect( m_transactionDep, SIGNAL( Finished(Exit::Value, uint) ), this, SLOT( depFinished(Exit::Value, uint) ) );
		// Create a KProgressDialog to don't upset the user
		m_waitPD = new KProgressDialog(this, i18n("Wait - KPackageKit"), i18n("Checking dependant packages") );
		m_waitPD->progressBar()->setMinimum(0);
		m_waitPD->progressBar()->setMaximum(0);
		m_waitPD->setAutoClose(false);
		m_waitPD->setModal(true);
		m_pbTimer->start(5);
		m_waitPD->show();
		m_transactionDep->getDepends("~installed", m_reqDepPackages.takeFirst(), true);
	    }
        }
	else
	    KMessageBox::error( this, i18n("Sorry, your backend does not support installing packages"), i18n("Erro KPackageKit") );
    }
    else {
        qDebug() << "task else";
        KDialog::slotButtonClicked(KDialog::Ok);
    }
}

void PkReviewChanges::reqFinished(Exit::Value status, uint /*runtime*/)
{
    qDebug() << "reqFinished";
    if (status == Exit::Success) {
        if ( m_reqDepPackages.isEmpty() ) {
	    m_pbTimer->stop();
	    delete m_waitPD;
	    m_waitPD = 0;
	    if ( m_pkgModelReq->rowCount( QModelIndex() ) > 0 ) {
		PkRequirements *requimentD = new PkRequirements( i18n("The following packages must also be removed"), m_pkgModelReq, this );
		connect( requimentD, SIGNAL( okClicked() ), this, SLOT( removePackages() ) );
		connect( requimentD, SIGNAL( cancelClicked() ), this, SLOT( close() ) );
		requimentD->show();
            }
	    else
	        removePackages();
	}
	else
	    m_transactionReq->getRequires("installed", m_reqDepPackages.takeFirst(), true);
    }
    else {
        m_pbTimer->stop();
	delete m_waitPD;
	m_waitPD = 0;
	// TODO inform the user
        qDebug() << "getReq Failed: " << status;
	m_reqDepPackages.clear();
        checkTask();
    }
    qDebug() << "reqFinished2";
}

void PkReviewChanges::removePackages()
{
    qDebug() << "removePackages";
    m_trans = m_daemon->newTransaction();
    PkTransaction *frm = new PkTransaction(m_trans, i18n("Remove Packages"), this);
    connect( frm, SIGNAL( Finished(bool) ), this, SLOT( remFinished(bool) ) );
    m_trans->removePackages(m_remPackages);
    frm->show();
    qDebug() << "finished remove";
}

void PkReviewChanges::depFinished(Exit::Value status, uint /*runtime*/)
{
    qDebug() << "depFinished";
    if (status == Exit::Success) {
        if ( m_reqDepPackages.isEmpty() ) {
	    m_pbTimer->stop();
	    delete m_waitPD;
	    m_waitPD = 0;
	    if ( m_pkgModelDep->rowCount( QModelIndex() ) > 0 ) {
		PkRequirements *requimentD = new PkRequirements( i18n("The following packages must also be installed"), m_pkgModelDep, this );
		connect( requimentD, SIGNAL( okClicked() ), this, SLOT( installPackages() ) );
		connect( requimentD, SIGNAL( cancelClicked() ), this, SLOT( close() ) );
		requimentD->show();
            }
	    else
	        installPackages();
	}
	else
	    m_transactionDep->getDepends("~installed", m_reqDepPackages.takeFirst(), true);
    }
    else {
        m_pbTimer->stop();
	delete m_waitPD;
	m_waitPD = 0;
        qDebug() << "getDep Failed: " << status;
	m_reqDepPackages.clear();
        checkTask();
    }
    qDebug() << "depFinished2";
}

void PkReviewChanges::installPackages()
{
    qDebug() << "installPackages";
    m_trans = m_daemon->newTransaction();
    PkTransaction *frm = new PkTransaction(m_trans, QString(i18n("Install Packages")), this);
    connect( frm, SIGNAL( Finished(bool) ), this, SLOT( addFinished(bool) ) );
    m_trans->installPackages(m_addPackages);
    frm->show();
    qDebug() << "finished install";
}

void PkReviewChanges::remFinished(bool error)
{
    if (error) {
        KMessageBox::error( this, i18n("Sorry an error ocoured"), i18n("Erro KPackageKit") );
	setButtons( KDialog::Close );
    }
    else {
        m_remPackages.clear();
	checkTask();
    }
}

void PkReviewChanges::addFinished(bool error)
{
    if (error) {
        KMessageBox::error( this, i18n("Sorry an error ocoured"), i18n("Erro KPackageKit") );
	setButtons( KDialog::Close );
    }
    else {
        m_addPackages.clear();
	checkTask();
    }
}

void PkReviewChanges::slotButtonClicked(int button)
{
    switch(button) {
        case KDialog::Cancel :
            close();
            break;
        case KDialog::Apply :
            doAction();
            break;
        default :
            KDialog::slotButtonClicked(button);
    }
}

void PkReviewChanges::resizeEvent ( QResizeEvent * event )
{
    QWidget::resizeEvent(event);
    updateColumnsWidth();
}

bool PkReviewChanges::event ( QEvent * event )
{
    switch (event->type()) {
        case QEvent::PolishRequest:
        case QEvent::Polish:
            updateColumnsWidth(true);
            break;
        default:
            break;
    }

    return QWidget::event(event);
}

void PkReviewChanges::updateColumnsWidth(bool force)
{
    m_viewWidth = packageView->viewport()->width();

    if (force) {
        m_viewWidth -= style()->pixelMetric(QStyle::PM_ScrollBarExtent) + UNIVERSAL_PADDING;
    }

    packageView->setColumnWidth(0, m_pkgDelegate->columnWidth(0, m_viewWidth));
    packageView->setColumnWidth(1, m_pkgDelegate->columnWidth(1, m_viewWidth));
}

#include "PkReviewChanges.moc"
