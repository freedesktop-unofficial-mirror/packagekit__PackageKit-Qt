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

#ifndef PKNOTIFY_H
#define PKNOTIFY_H

#include <QPackageKit>
#include <KNotification>

using namespace PackageKit;

namespace kpackagekit {
 
class PkNotify : public QObject
{
Q_OBJECT
public:
    PkNotify( QObject *parent=0 );
    ~PkNotify();

    void displayUpdates();
    void finishInstallingRebootReq();
    void updatesBeingInstalled();
    
private slots:
    void UpdatesFinished(Exit::Value status, uint runtime);
    void GotPackage(Package *);
    void updatesActions(uint action);

private:
    KNotification *updatesNotification;
    Daemon *m_daemon;
    Transaction *m_pkClient_updates;
    QList<Package *> packages;
};

}

#endif
