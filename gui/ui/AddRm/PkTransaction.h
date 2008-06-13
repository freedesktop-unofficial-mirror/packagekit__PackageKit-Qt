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

#ifndef PKTRANSACTION_H
#define PKTRANSACTION_H

#include <KDialog>

// #include "PkAddRm_Model.h"
#include "ui_PkTransaction.h"
#include "../../../lib/QPackageKit.h"

using namespace PackageKit;

class PkTransaction : public KDialog, Ui::PkTransaction
{
    Q_OBJECT
public:
    PkTransaction( Transaction *trans, QString &caption, QWidget *parent=0);
    ~PkTransaction();

public slots:
//     void reqFinished(Exit::Value status, uint runtime);
    void Finished(Exit::Value status, uint runtime);
    void ErrorCode(const QString &one, const QString &two);
    void StatusChanged(Status::Value v);
    void ProgressChanged(uint percentage, uint subpercentage, uint elapsed, uint remaining);
private:
//     PkAddRmModel *m_pkg_model_req;
    Transaction *m_trans;
    QTimer m_notifyT;
    QTimer *m_pbTimer;

private slots:
//     void doAction();
    void currPackage(Package *);
    void updateProgress();

protected slots:
    virtual void slotButtonClicked(int button);
};

#endif