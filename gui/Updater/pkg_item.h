/***************************************************************************
 *   Copyright (C) 2008 by Daniel Nicoletti                                *
 *   daniel@whitemoon                                                      *
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
#ifndef PACKAGE_ITEM_H
#define PACKAGE_ITEM_H

#include "../../lib/QPackageKit.h"

#include <QList>
#include <QVariant>

using namespace PackageKit;

/**
	@author Daniel Nicoletti <daniel@whitemoon>
*/
class PackageItem{
public:
    PackageItem(Package *pkg, PackageItem *parent = 0);
    PackageItem();

    ~PackageItem();

    void appendChild(PackageItem *child);

    PackageItem *child(int row);
    int childCount() const;
    int columnCount() const;
    Package *data() const;
    int row() const;
    PackageItem *parent();
    QString name();

private:
    QList<PackageItem*> childItems;
    Package *m_pkg;
    PackageItem *parentItem;
};

#endif
