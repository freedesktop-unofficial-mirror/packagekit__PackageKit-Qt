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

#include "PkSettings.h"
#include <KDebug>
#include <KConfig>
#include <KGlobal>

// 1 Hour = 3600 in Epoch
// 1 Day = 86400 in Epoch (24 Hours)
// 1 Week = 604800 in Epoch (7 Days / 168 Hours)
// 1 Month = 2628000 in Epoch

 
PkSettings::PkSettings( QWidget *parent ) : QWidget( parent )
{
    setupUi( this );
//     m_kcfDM = new KConfigDialogManager(this, m_pk_cfgSkell = new PkConfigSkell());
    connect( notifyUpdatesCB, SIGNAL(stateChanged(int)), this, SLOT(checkChanges(int)) );
    connect( notifyLongTasksCB, SIGNAL(stateChanged(int)), this, SLOT(checkChanges(int)) );
}

void PkSettings::checkChanges(int)
{
    kDebug() << "checkChanges " << notifyUpdatesCB->checkState();
    KConfig config("KPackageKit");
    KConfigGroup smartIconGroup( &config, "SmartIcon" );
    if ( notifyUpdatesCB->checkState() !=
         (Qt::CheckState) smartIconGroup.readEntry( "notifyUpdatesCB", (int) Qt::Checked)
        ||
         notifyLongTasksCB->checkState() !=
         (Qt::CheckState) smartIconGroup.readEntry( "notifyLongTasksCB", (int) Qt::Checked) )
        emit(changed(true));
    else
        emit(changed(false));
}

void PkSettings::load()
{
    kDebug() << "load";
    KConfig config("KPackageKit");
    KConfigGroup smartIconGroup( &config, "SmartIcon" );
    notifyUpdatesCB->setCheckState( (Qt::CheckState) smartIconGroup.readEntry( "notifyUpdatesCB",
        (int) Qt::Checked) );
    notifyLongTasksCB->setCheckState( (Qt::CheckState) smartIconGroup.readEntry( "notifyLongTasksCB",
        (int) Qt::Checked) );
}

void PkSettings::save()
{
    kDebug() << "save";
    KConfig config("KPackageKit");
    KConfigGroup smartIconGroup( &config, "SmartIcon" );
    smartIconGroup.writeEntry( "notifyUpdatesCB", (int) notifyUpdatesCB->checkState() );
    smartIconGroup.writeEntry( "notifyLongTasksCB", (int) notifyLongTasksCB->checkState() );
config.sync();
}

void PkSettings::defaults()
{
    kDebug() << "defaults";
    notifyUpdatesCB->setCheckState(Qt::Checked);
    notifyLongTasksCB->setCheckState(Qt::Checked);
    emit(checkChanges(0));
}

#include "PkSettings.moc" 
