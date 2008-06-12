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
#include "pkg_item.h"

#include <QStringList>

PackageItem::PackageItem(Package *pkg, PackageItem *parent)
 : parentItem(parent), m_pkg(pkg)
{
}

PackageItem::PackageItem()
 : parentItem(0)
{
}

QString PackageItem::name()
{
    if (parentItem)
        if ( m_pkg->name().isEmpty() )
            return QString::number( childCount() ) + " " + m_pkg->info();
        else
            return m_pkg->name() + " - " + m_pkg->version() + " (" + m_pkg->arch() + ")";
    else
        return QString();
}

PackageItem::~PackageItem()
{
    qDeleteAll(childItems);
}

void PackageItem::appendChild(PackageItem *item)
{
    childItems.append(item);
}

PackageItem *PackageItem::child(int row)
{
    return childItems.value(row);
}

int PackageItem::childCount() const
{
    return childItems.count();
}

int PackageItem::columnCount() const
{
    return 1;
}

Package *PackageItem::data() const
{
    return m_pkg;
}

PackageItem *PackageItem::parent()
{
    return parentItem;
}

int PackageItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<PackageItem*>(this));

    return 0;
}
