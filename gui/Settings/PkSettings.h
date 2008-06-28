/***************************************************************************
 *   Copyright (C) 2008 by Daniel Nicoletti   *
 *   mirttex85-pk@yahoo.com.br   *
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

#ifndef PKSETTINGS_H
#define PKSETTINGS_H

#include <kconfigdialogmanager.h>
// #include "PkConfigSkell.h"
#include "ui_PkSettings.h"
 
class PkSettings : public QWidget, public Ui::PkSettings
{
Q_OBJECT

public:
    PkSettings( QWidget *parent=0 );
public slots:
    void load();
    void save();
    void defaults();
    void checkChanges(int state);
signals:
    void changed(bool state);

// public:
//     KConfigDialogManager *m_kcfDM;
//     PkConfigSkell *m_pk_cfgSkell;
};

#endif
