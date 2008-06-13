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

#ifndef PKREVIEWCHANGES_H
#define PKREVIEWCHANGES_H

#include <KDialog>

#include "PkDelegate.h"
#include "PkAddRm_Model.h"
#include "ui_PkReviewChanges.h"
#include "../../../lib/QPackageKit.h"

using namespace PackageKit;

class PkReviewChanges : public KDialog, Ui::PkReviewChanges
{
    Q_OBJECT
public:
    PkReviewChanges( const QList<Package*> &packages, QWidget *parent=0);
    ~PkReviewChanges();

public slots:
    void remFinished(Exit::Value status, uint runtime);
    void addFinished(Exit::Value status, uint runtime);
    void ErrorCode(const QString &one, const QString &two);
//     void StatusChanged(Status::Value v);
    void ProgressChanged(uint percentage, uint subpercentage, uint elapsed, uint remaining);
    void reqFinished(Exit::Value status, uint runtime);
    void depFinished(Exit::Value status, uint runtime);
    void installPackages();
    void removePackages();

private:
    PkAddRmModel *m_pkgModelMain, *m_pkgModelReq, *m_pkgModelDep;
    PkDelegate *m_pkgDelegate;
    Daemon *m_daemon;
    Transaction *m_trans;
    Transaction *m_transactionReq;
    Transaction *m_transactionDep;
    QTimer m_notifyT;
    QTimer *m_pbTimer;
    int m_viewWidth;

    void updateColumnsWidth(bool force = false);
    void doAction();
    void checkTask();

    QList<Package*> m_remPackages;
    QList<Package*> m_addPackages;
    QList<Package*> m_reqDepPackages;

private slots:
    void currPackage(Package *);
    void updateProgress();

protected slots:
    virtual void slotButtonClicked(int button);

protected:
    virtual void resizeEvent( QResizeEvent * event );
    virtual bool event( QEvent * event );
};

#endif
