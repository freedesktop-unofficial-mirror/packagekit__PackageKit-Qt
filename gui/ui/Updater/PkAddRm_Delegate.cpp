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

#include "PkAddRm_Delegate.h"

#include <cmath>
#include <QtCore/QtCore>
#include <KDebug>
#include <KIconLoader>

#include "PkAddRm_Model.h"

#define FAV_ICON_SIZE 24
#define EMBLEM_ICON_SIZE 16
#define UNIVERSAL_PADDING 6
#define FADE_LENGTH 32
#define MAIN_ICON_SIZE 48
#define DROPDOWN_PADDING 2
#define DROPDOWN_SEPARATOR_HEIGHT 32

PkAddRmDelegate::PkAddRmDelegate(QObject * parent)
        : QItemDelegate(parent), m_favoriteIcon("bookmarks"),
        m_favoriteAddIcon("list-add"), m_removeIcon("list-remove")/*,
        m_onFavoriteIconItem(NULL)*/
{
//     m_parent = (PkAddRm *) parent;
}

void PkAddRmDelegate::paint(QPainter *painter,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
{

//     index.model()->data(index, Qt::EditRole).toInt();

//     KCategorizedItemsViewModels::AbstractItem * item =
//         getItemByProxyIndex(index);
//     if (!item) return;

    QStyleOptionViewItemV4 opt(option);
    QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter, opt.widget);

    switch (index.column()) {
    case 0:
        paintColMain(painter, option, index);
        break;
    case 1:
        paintColFav(painter, option, index);
        break;
//     case 2:
//         paintColRemove(painter, option, index);
//         break;
    default:
        kDebug() << "unexpected column";
    }
}

void PkAddRmDelegate::paintColMain(QPainter *painter,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    int left = option.rect.left();
    int top = option.rect.top();
    int width = option.rect.width();

    bool leftToRight = (painter->layoutDirection() == Qt::LeftToRight);

    // selects the mode to paint the icon based on the info field
    QIcon::Mode iconMode = ( index.model()->data(index, PkAddRmModel::InstalledRole).toBool() ? QIcon::Normal : QIcon::Disabled);
//     if ( index.model()->data(index, PkAddRmModel::InstalledRole).toBool() )
//         QIcon::Mode iconMode = QIcon::Normal;
//     else
//         QIcon::Mode iconMode = QIcon::Disabled;

    QColor foregroundColor = (option.state.testFlag(QStyle::State_Selected))?
        option.palette.color(QPalette::HighlightedText):option.palette.color(QPalette::Text);

    // Painting main column
    QStyleOptionViewItem local_option_title(option);
    QStyleOptionViewItem local_option_normal(option);

    local_option_title.font.setBold(true);
    local_option_title.font.setPointSize(local_option_title.font.pointSize() + 2);

    QPixmap pixmap(option.rect.size());
    pixmap.fill(Qt::transparent);
    QPainter p(&pixmap);
    p.translate(-option.rect.topLeft());

    QLinearGradient gradient;

    // Easier to ask the model for the data
    QString title = index.model()->data(index, Qt::DisplayRole).toString();
    QString description = index.model()->data(index, PkAddRmModel::SummaryRole).toString();

    // Painting

    // Text
    int textInner = 2 * UNIVERSAL_PADDING + MAIN_ICON_SIZE;

    p.setPen(foregroundColor);
    p.setFont(local_option_title.font);
    p.drawText(
            left + (leftToRight ? textInner : 0),
            top + UNIVERSAL_PADDING,
            width - textInner, MAIN_ICON_SIZE / 2,
            Qt::AlignBottom | Qt::AlignLeft, title);
    p.setFont(local_option_normal.font);
    p.drawText(
            left + (leftToRight ? textInner : 0),
            top + UNIVERSAL_PADDING + MAIN_ICON_SIZE / 2,
            width - textInner, MAIN_ICON_SIZE / 2,
            Qt::AlignTop | Qt::AlignLeft, description);

    // Main icon
    index.model()->data(index, Qt::DecorationRole).value<QIcon>().paint(&p,
            leftToRight ? left + UNIVERSAL_PADDING : left + width - UNIVERSAL_PADDING - MAIN_ICON_SIZE,
            top + UNIVERSAL_PADDING,
            MAIN_ICON_SIZE, MAIN_ICON_SIZE, Qt::AlignCenter, iconMode);

    // Counting the number of emblems for this item
    int emblemCount = 0;
//     QPair < Filter, QIcon * > emblem;
//     foreach (emblem, m_parent->m_emblems) {
//         if (item->passesFiltering(emblem.first)) ++emblemCount;
//     }

    // Gradient part of the background - fading of the text at the end
    if (leftToRight) {
        gradient = QLinearGradient(left + width - UNIVERSAL_PADDING - FADE_LENGTH, 0,
                left + width - UNIVERSAL_PADDING, 0);
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, Qt::transparent);
    } else {
        gradient = QLinearGradient(left + UNIVERSAL_PADDING, 0,
                left + UNIVERSAL_PADDING + FADE_LENGTH, 0);
        gradient.setColorAt(0, Qt::transparent);
        gradient.setColorAt(1, Qt::white);
    }

    QRect paintRect = option.rect;
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.fillRect(paintRect, gradient);

    if (leftToRight) {
        gradient.setStart(left + width
                - emblemCount * (UNIVERSAL_PADDING + EMBLEM_ICON_SIZE) - FADE_LENGTH, 0);
        gradient.setFinalStop(left + width
                - emblemCount * (UNIVERSAL_PADDING + EMBLEM_ICON_SIZE), 0);
    } else {
        gradient.setStart(left + UNIVERSAL_PADDING
                + emblemCount * (UNIVERSAL_PADDING + EMBLEM_ICON_SIZE), 0);
        gradient.setFinalStop(left + UNIVERSAL_PADDING
                + emblemCount * (UNIVERSAL_PADDING + EMBLEM_ICON_SIZE) + FADE_LENGTH, 0);
    }
    paintRect.setHeight(UNIVERSAL_PADDING + MAIN_ICON_SIZE / 2);
    p.fillRect(paintRect, gradient);

    // Emblems icons
    p.setCompositionMode(QPainter::CompositionMode_SourceOver);
//     int emblemLeft = leftToRight ? (left + width - EMBLEM_ICON_SIZE) : left; // - FAV_ICON_SIZE - 2 * UNIVERSAL_PADDING
//     foreach (emblem, m_parent->m_emblems) {
//         if (item->passesFiltering(emblem.first)) {
//             emblem.second->paint(&p,
//                     emblemLeft, top + UNIVERSAL_PADDING,
//                     EMBLEM_ICON_SIZE, EMBLEM_ICON_SIZE, Qt::AlignCenter, iconMode);
//             if (leftToRight) {
//                 emblemLeft -= UNIVERSAL_PADDING + EMBLEM_ICON_SIZE;
//             } else {
//                 emblemLeft += UNIVERSAL_PADDING + EMBLEM_ICON_SIZE;
//             }
//         }
//     }
    p.end();

    painter->drawPixmap(option.rect.topLeft(), pixmap);
}

void PkAddRmDelegate::paintColFav(QPainter *painter,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//     int left = option.rect.left();
//     int top = option.rect.top();
//     int width = option.rect.width();
//
//     // Painting favorite icon column
//
//     if (! (option.state & QStyle::State_MouseOver) && m_onFavoriteIconItem == item)
//         m_onFavoriteIconItem = NULL;
//
//     QIcon::Mode iconMode = QIcon::Normal;
//     if (!item->isFavorite()) {
//         iconMode = QIcon::Disabled;
//     } else if (option.state & QStyle::State_MouseOver) {
//         iconMode = QIcon::Active;
//     }
//
//     m_favoriteIcon.paint(painter,
//             left + width - FAV_ICON_SIZE - UNIVERSAL_PADDING, top + UNIVERSAL_PADDING,
//             FAV_ICON_SIZE, FAV_ICON_SIZE, Qt::AlignCenter, iconMode);
//
//     const KIcon * icon = (item->isFavorite())? & m_removeIcon : & m_favoriteAddIcon;
//
//     if ((option.state & QStyle::State_MouseOver) && (m_onFavoriteIconItem != item))
//         icon->paint(painter,
//                 left + width - EMBLEM_ICON_SIZE - UNIVERSAL_PADDING, top + UNIVERSAL_PADDING,
//                 EMBLEM_ICON_SIZE, EMBLEM_ICON_SIZE, Qt::AlignCenter, iconMode);
}

// void PkAddRmDelegate::paintColRemove(QPainter *painter,
//         const QStyleOptionViewItem &option, const QModelIndex &index) const
// {
//     // Painting remove icon column
//     int running = item->running();
//     if (!running) {
//         return;
//     }
//
//     int left = option.rect.left();
//     int top = option.rect.top();
//     int width = option.rect.width();
//
//     QIcon::Mode iconMode = QIcon::Normal;
//     if (option.state & QStyle::State_MouseOver) {
//         iconMode = QIcon::Active;
//     }
//
//     m_removeIcon.paint(painter,
//             left + width - FAV_ICON_SIZE - UNIVERSAL_PADDING, top + UNIVERSAL_PADDING,
//             FAV_ICON_SIZE, FAV_ICON_SIZE, Qt::AlignCenter, iconMode);
//
//     if (running == 1) {
//         return;
//     }
//     //paint number
//     QColor foregroundColor = (option.state.testFlag(QStyle::State_Selected))?
//         option.palette.color(QPalette::HighlightedText):option.palette.color(QPalette::Text);
//     painter->setPen(foregroundColor);
//     painter->setFont(option.font);
//     painter->drawText(
//             left + UNIVERSAL_PADDING, //FIXME might be wrong
//             top + UNIVERSAL_PADDING + MAIN_ICON_SIZE / 2,
//             width - 2 * UNIVERSAL_PADDING, MAIN_ICON_SIZE / 2,
//             Qt::AlignCenter, QString::number(running));
// }

// bool PkAddRmDelegate::editorEvent(QEvent *event,
//                                QAbstractItemModel *model,
//                                const QStyleOptionViewItem &option,
//                                const QModelIndex &index)
// {
//     if (event->type() == QEvent::MouseButtonPress) {
//         KCategorizedItemsViewModels::AbstractItem * item = getItemByProxyIndex(index);
//         if (index.column() == 1) {
//             m_onFavoriteIconItem = item;
//             item->setFavorite(!item->isFavorite());
//             return true;
//         } else if (index.column() == 2 && item->running()) {
//             item->setRunning(0);
//             emit destroyApplets(item->name());
//             return true;
//         }
//     }
//
//     return QItemDelegate::editorEvent(event, model, option, index);
// }

QSize PkAddRmDelegate::sizeHint(const QStyleOptionViewItem &option,
        const QModelIndex &index ) const
{
    Q_UNUSED(option);

    //Q_UNUSED(index);
    int width = (index.column() == 0) ? 0 : FAV_ICON_SIZE;
    return QSize(width, MAIN_ICON_SIZE + 2 * UNIVERSAL_PADDING);
}

int PkAddRmDelegate::columnWidth (int column, int viewWidth) const {
    if (column != 0) {
        return FAV_ICON_SIZE + 2 * UNIVERSAL_PADDING;
    } else return viewWidth - 2 * columnWidth(1, viewWidth);
}

#include "PkAddRm_Delegate.moc"

