/***************************************************************************
 *   Copyright (C) 2008 by Daniel Nicoletti                                *
 *   mirttex85-pk@yahoo.com.br                                             *
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

#ifndef KPACKAGEKIT_H
#define KPACKAGEKIT_H

#include <KDEDModule>
#include <KDirWatch>
#include <QTimer>

class KPackageKit : public KDEDModule
{
Q_OBJECT

public:
    KPackageKit(QObject *parent, const QList<QVariant>&);
    ~KPackageKit();
private:
    QTimer *m_qtimer;
    KDirWatch *m_confWatch;
private slots:
    void init();
    void read();
    void write();
    void checkUpdates();
};

#endif