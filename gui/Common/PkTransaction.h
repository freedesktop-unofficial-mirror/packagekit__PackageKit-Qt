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

#ifndef PKTRANSACTION_H
#define PKTRANSACTION_H

#include <KDialog>

#include "ui_PkTransaction.h"
#include <QPackageKit>

using namespace PackageKit;

class PkTransaction : public KDialog, Ui::PkTransaction
{
    Q_OBJECT
public:
    PkTransaction( Transaction  *trans, QString caption, QWidget *parent=0);
    ~PkTransaction();

signals:
    void Finished(bool error);

private:
    Transaction *m_trans;
    QTimer *m_pbTimer;

private slots:
    void Finished(Exit::Value status, uint runtime);
    void ErrorCode(Error::Value v, const QString &details);
    void StatusChanged(Status::Value v);
    void currPackage(Package *);
    void updateProgress();
    void ProgressChanged(uint percentage, uint subpercentage, uint elapsed, uint remaining);

protected slots:
    virtual void slotButtonClicked(int button);
};

#endif
