/*
 *   Copyright (C) 2007 Ivan Cukic <ivan.cukic+kde@gmail.com>
 *   Copyright (C) 2008 Daniel Nicoletti <mirttex85-pk@yahoo.com.br>
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

#ifndef PKADDRMDELEGATE_H
#define PKADDRMDELEGATE_H

#include <QtCore/QtCore>
#include <QtGui/QtGui>

#include <KIcon>

/**
 * Delegate for displaying the items
 */
class PkAddRmDelegate: public QItemDelegate
{
    Q_OBJECT

public:
    PkAddRmDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    int columnWidth (int column, int viewWidth) const;

//     bool editorEvent(QEvent *event,
//                      QAbstractItemModel *model,
//                      const QStyleOptionViewItem &option,
//                      const QModelIndex &index);

Q_SIGNALS:
    void destroyApplets(const QString name);
private:

//     KCategorizedItemsView * m_parent;
    KIcon m_favoriteIcon;
    KIcon m_favoriteAddIcon;
    KIcon m_removeIcon;

//     mutable KCategorizedItemsViewModels::AbstractItem * m_onFavoriteIconItem;

    void paintColMain(QPainter *painter,
            const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintColFav(QPainter *painter,
            const QStyleOptionViewItem &option, const QModelIndex &index) const;
//     void paintColRemove(QPainter *painter,
//             const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif /*KCATEGORIZEDITEMSVIEWDELEGATE_H_*/
