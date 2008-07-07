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

#ifndef PKUPDATE_H
#define PKUPDATE_H

#include <QPackageKit>

#include "PkAddRm_Model.h"
#include "PkAddRm_Delegate.h"
#include "ui_PkUpdate.h"

using namespace PackageKit;
 
class PkUpdate : public QWidget, public Ui::PkUpdate
{
Q_OBJECT
public:
    PkUpdate( QWidget *parent=0 );

private slots:
    void on_updatePB_clicked();
    void on_refreshPB_clicked();
    void on_historyPB_clicked();
    void refreshCacheFinished(bool error);

private:
    PkAddRmModel *m_pkg_model_updates;
    PkAddRmDelegate *pkg_delegate;
    Daemon *m_daemon;
    Transaction *m_pkClient_updates;
};

#endif
