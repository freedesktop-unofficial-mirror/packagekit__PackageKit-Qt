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

#ifndef PKADDRM_TRANSACTION_H
#define PKADDRM_TRANSACTION_H

#include <KDialog>
// #include <QtCore/QtCore>

#include "PkAddRm_Model.h"
#include "ui_PkAddRm_Transaction.h"
#include "../../../lib/QPackageKit.h"

using namespace PackageKit;

class PkAddRmTransaction : public KDialog, Ui::PkAddRmTransaction
{
    Q_OBJECT
public:
    PkAddRmTransaction( Package *pkg, QWidget *parent=0);
    ~PkAddRmTransaction();

public slots:
//     void Description(Package *p, const QString &license, const QString &group, const QString &detail, const QString &url, qulonglong size);
//     void Files(Package *p, QStringList files);
    void reqFinished(Exit::Value status, uint runtime);
    void Finished(Exit::Value status, uint runtime);
    void Message(const QString &one, const QString &two);
    void StatusChanged(Status::Value v);
    void ProgressChanged(uint percentage, uint subpercentage, uint elapsed, uint remaining);
private:
    PkAddRmModel *m_pkg_model_req;
    Transaction *m_pkClient_req, *m_pkClient_action;
    QTimer m_notifyT;
    Package *m_targetPackage;

private slots:
    void doAction();
    void currPackage(Package *);

private:
    Daemon *m_daemon;

protected slots:
    virtual void slotButtonClicked(int button);
};

#endif
