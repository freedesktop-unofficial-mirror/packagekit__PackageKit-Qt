#ifndef CHECKBOXMENU_H
#define CHECKBOXMENU_H

#include <QtGui>

class FilterMenu
{
Q_OBJECT

public:
    FilterMenu(const QStringList &filters, QWidget *parent = 0);
    QString filters();

private:
    QToolButton *m_tool_bt;
    QMenu *menu;
    // We need to keep a list to build the filters string
    QList<QAction*> actions;
};

#endif
