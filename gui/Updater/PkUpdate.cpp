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

#include "PkUpdate.h"
#include "../Common/PkTransaction.h"

#include <KMessageBox>
 
PkUpdate::PkUpdate( QWidget *parent ) : QWidget( parent )
{
    setupUi( this );
    descriptionKTB->hide();

    //initialize the model, delegate, client and  connect it's signals
    treeView->setModel(m_pkg_model_updates = new PkAddRmModel(this));
    treeView->setItemDelegate(pkg_delegate = new PkAddRmDelegate(this));

    // Create a new daemon
    m_daemon = new Daemon(this);

    m_pkClient_updates = m_daemon->newTransaction();
    connect( m_pkClient_updates, SIGNAL(GotPackage(Package *)), m_pkg_model_updates, SLOT(addPackage(Package *)) );
    connect( m_pkClient_updates, SIGNAL(Finished(Exit::Value, uint)), this, SLOT(Finished(Exit::Value, uint)) );
    connect( m_pkClient_updates, SIGNAL(Files(Package *, QStringList)), this, SLOT(Files(Package *, QStringList)) );
    connect( m_pkClient_updates, SIGNAL( Message(const QString&, const QString&) ), this, SLOT( Message(const QString&, const QString&) ) );
    connect( m_pkClient_updates, SIGNAL( ErrorCode(const QString&, const QString&) ), this, SLOT( Message(const QString&, const QString&) ) );
    m_pkClient_updates->getUpdates("none");
}

void PkUpdate::on_updatePB_clicked()
{
    qDebug() << "update";
}

void PkUpdate::on_refreshPB_clicked()
{
    qDebug() << "refresh";
    Transaction *m_trans = m_daemon->newTransaction();
  /*  if (*/ m_trans->refreshCache(true);/* ) {*/
        PkTransaction *frm = new PkTransaction(m_trans, i18n("Refresh Cache"), this);
        connect( frm, SIGNAL( Finished(bool) ), this, SLOT( remFinished(bool) ) );
        frm->show();
//     }
//     else
//         KMessageBox::error( this, i18n("Authentication failed"), i18n("KPackageKit") );

}

void PkUpdate::on_historyPB_clicked()
{
    qDebug() << "history";
    m_pkg_model_updates->clear();
// qDebug() << m_pkg_model_updates->rowCount();
}

#include "PkUpdate.moc" 
