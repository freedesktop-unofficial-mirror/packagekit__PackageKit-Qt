/***************************************************************************
 *   Copyright (C) 2007 by Daniel Nicoletti   *
 *   mirttex@users.sourceforge.net   *
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

#include "PkAddRm_Model.h"
#include "PkAddRm_Delegate.h"

#include "ui_PkAddRm.h"

using namespace PackageKit;

class PkAddRm : public QWidget, public Ui::PkAddRm
{
    Q_OBJECT
public:
    PkAddRm( QWidget *parent=0 );
    ~PkAddRm();
public slots:
    void on_searchPB_clicked();
    void on_actionPB_clicked();
    void on_groupsCB_currentIndexChanged( const QString & text );
    void on_packageView_pressed( const QModelIndex & index );
    void Description(Package *p, const QString& license, const QString& group, const QString& detail, const QString& url, qulonglong size);
    void Files(Package *p, QStringList files);
    void Finished(Exit::Value status, uint runtime);
private:
    PkAddRmModel *m_pkg_model_main;
    PkAddRmModel *m_pkg_model_dep;
    PkAddRmModel *m_pkg_model_req;
    PkAddRmDelegate *pkg_delegate;
    Client *m_pkClient_main;
    Client *m_pkClient_dep;
    Client *m_pkClient_req;
    QTimer m_notifyT;
private slots:
    void notifyUpdate();
//Filter Menu
public:
    void FilterMenu(const QStringList &filters);
    QString filters();

private:
    QMenu *m_toolQM;
    // We need to keep a list to build the filters string
    QList<QAction*> actions;

};

#endif
