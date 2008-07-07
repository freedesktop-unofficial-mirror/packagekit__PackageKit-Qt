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
#include <KLocale>

#define HOURLY 3600
#define DAILY 86400
#define WEEKLY 604800
#define MONTHLY 2628000
#define NEVER 0
 
PkSettings::PkSettings( QWidget *parent ) : QWidget( parent )
{
    setupUi( this );
    
    // Create a new daemon
    m_daemon = new Daemon(this);
    
    uint actions = m_daemon->getActions();

    if ( !(actions & Actions::Refresh_cache) ) {
        intervalL->setEnabled(false);
	intervalCB->setEnabled(false);
    }
    
    intervalCB->addItem(i18n("Hourly"), HOURLY );
    intervalCB->addItem(i18n("Daily"), DAILY );
    intervalCB->addItem(i18n("Weekly"), WEEKLY );
    intervalCB->addItem(i18n("Monthly"), MONTHLY );
    intervalCB->addItem(i18n("Never"), NEVER );

    connect( notifyUpdatesCB, SIGNAL( stateChanged(int) ), this, SLOT( checkChanges(int) ) );
    connect( notifyLongTasksCB, SIGNAL( stateChanged(int) ), this, SLOT( checkChanges(int) ) );
    connect( intervalCB, SIGNAL( currentIndexChanged(int) ), this, SLOT( checkChanges(int) ) );
}

void PkSettings::checkChanges(int)
{
    KConfig config("KPackageKit");
    KConfigGroup smartIconGroup( &config, "SmartIcon" );
    KConfigGroup checkUpdateGroup( &config, "CheckUpdate" );
    if ( notifyUpdatesCB->checkState() !=
         (Qt::CheckState) smartIconGroup.readEntry( "notifyUpdatesCB", (int) Qt::Checked)
        ||
         notifyLongTasksCB->checkState() !=
         (Qt::CheckState) smartIconGroup.readEntry( "notifyLongTasksCB", (int) Qt::Checked)
	||
	 intervalCB->itemData( intervalCB->currentIndex() ).toUInt() !=
	 (uint) checkUpdateGroup.readEntry( "interval", DAILY ) )
        emit(changed(true));
    else
        emit(changed(false));
}

void PkSettings::load()
{
    KConfig config("KPackageKit");
    KConfigGroup smartIconGroup( &config, "SmartIcon" );
    notifyUpdatesCB->setCheckState( (Qt::CheckState) smartIconGroup.readEntry( "notifyUpdatesCB",
        (int) Qt::Checked) );
    notifyLongTasksCB->setCheckState( (Qt::CheckState) smartIconGroup.readEntry( "notifyLongTasksCB",
        (int) Qt::Checked) );
    KConfigGroup checkUpdateGroup( &config, "CheckUpdate" );
    uint interval = checkUpdateGroup.readEntry( "interval", DAILY );
    int ret = intervalCB->findData(interval);
    if ( ret == -1 ) {
        // this is if someone change the file by hand...
        intervalCB->addItem( KGlobal::locale()->formatDuration(interval * 1000), interval );
	intervalCB->setCurrentIndex( intervalCB->count() - 1 );
    }
    else
        intervalCB->setCurrentIndex(ret);
}

void PkSettings::save()
{
    KConfig config("KPackageKit");
    KConfigGroup smartIconGroup( &config, "SmartIcon" );
    smartIconGroup.writeEntry( "notifyUpdatesCB", (int) notifyUpdatesCB->checkState() );
    smartIconGroup.writeEntry( "notifyLongTasksCB", (int) notifyLongTasksCB->checkState() );
    KConfigGroup checkUpdateGroup( &config, "CheckUpdate" );
    checkUpdateGroup.writeEntry( "interval", intervalCB->itemData( intervalCB->currentIndex() ).toUInt() );
}

void PkSettings::defaults()
{
    notifyUpdatesCB->setCheckState(Qt::Checked);
    notifyLongTasksCB->setCheckState(Qt::Checked);
    intervalCB->setCurrentIndex( intervalCB->findData(DAILY) );
    emit(checkChanges(0));
}

#include "PkSettings.moc" 
