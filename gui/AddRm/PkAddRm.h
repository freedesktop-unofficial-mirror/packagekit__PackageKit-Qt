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

#ifndef PKADDRM_H
#define PKADDRM_H

#include <QtGui/QtGui>
#include <QtCore/QtCore>

#include <KIcon>

#include "PkAddRm_Model.h"
#include "PkDelegate.h"

#include "../../lib/QPackageKit.h"
#include "ui_PkAddRm.h"

using namespace PackageKit;

class PkAddRm : public QWidget, public Ui::PkAddRm
{
    Q_OBJECT
public:
    PkAddRm( QWidget *parent=0 );
    ~PkAddRm();

public slots:
    void on_findPB_clicked();
    void on_groupsCB_currentIndexChanged( int index );
    void on_packageView_pressed( const QModelIndex &index );
    void Description( Package *p, const QString &license, const QString &group, const QString &detail, const QString &url, qulonglong size );
    void Files( Package *p, QStringList files );
    void Finished( Exit::Value status, uint runtime );
    void Message( const QString &one, const QString &two );
    void ErrorCode( Error::Value v, const QString &details );
    void StatusChanged( Status::Value v );
    void load();
    void save();

private:
    void infoHide();
    void infoShow();

    bool m_mTransRuning;//main trans
    PkAddRmModel *m_pkg_model_main;
    PkAddRmModel *m_pkg_model_dep;
    PkAddRmModel *m_pkg_model_req;
    PkDelegate *pkg_delegate;

    Daemon *m_daemon;
    Transaction *m_pkClient_main;
    Transaction *m_pkClient_desc;
    Transaction *m_pkClient_files;
    Transaction *m_pkClient_dep;
    Transaction *m_pkClient_req;

    QTimer m_notifyT;
    QTimer m_busyT;
    QMenu *m_toolQM;
    KIcon m_findIcon;
    KIcon m_cancelIcon;

    // We need to keep a list to build the filters string
    QList<QAction*> actions;
    void FilterMenu(const QStringList &filters);
    QString filters();

    void updateColumnsWidth(bool force = false);
    int m_viewWidth;
    void search();

private slots:
    void notifyUpdate();
    void updateProgress();
    void ProgressChanged(uint percentage, uint subpercentage, uint elapsed, uint remaining);

signals:
    void changed(bool state);

protected:
    virtual void resizeEvent ( QResizeEvent * event );
    virtual bool event ( QEvent * event );

};

#endif
