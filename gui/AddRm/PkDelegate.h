/*
 *   Copyright (C) 2007 Ivan Cukic <ivan.cukic+kde@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library/Lesser General Public License
 *   version 2, or (at your option) any later version, as published by the
 *   Free Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library/Lesser General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef PKDELEGATE_H
#define PKDELEGATE_H

#include <QtCore/QtCore>
#include <QtGui/QtGui>

#include <KIcon>

/**
 * Delegate for displaying the packages
 */
class PkDelegate: public QItemDelegate
{
    Q_OBJECT
    
public:
    PkDelegate(QObject *parent = 0);
    
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    int columnWidth (int column, int viewWidth) const;
        
    bool editorEvent(QEvent *event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index);

private:
    KIcon m_addIcon;
    KIcon m_removeIcon;

    void paintColMain(QPainter *painter,
            const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintColFav(QPainter *painter,
            const QStyleOptionViewItem &option, const QModelIndex &index) const;
    
    int calcItemHeight(const QStyleOptionViewItem &option) const;
};

#endif
