/*  This file is part of the KDE project
 *  Copyright (C) 2008 Daniel Nicoletti <dantti85-pk@yahoo.com.br>
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2
 *  as published by the Free Software Foundation.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301, USA.
 * 
 */

#include <kglobal.h>
#include <kstartupinfo.h>
#include <kcmdlineargs.h>
#include <kstandarddirs.h>
#include <knotification.h>
#include <KDebug>
#include <QStringList>

#include "kpk.h"

namespace kpackagekit {

Kpk::Kpk()
 : KUniqueApplication(), m_pkNotify(0)
{
    kDebug() << "abriu";
    m_smartSTI = new KSystemTrayIcon("applications-other");
}

Kpk::~Kpk()
{
}

int Kpk::newInstance()
{
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    if ( args->isSet("smart-icon") ) {
	kDebug() << "smart-icon";
	m_smartSTI->show();
    }
    if ( args->isSet("show-updates") ) {
	kDebug() << "Show Updates!";
	if (!m_pkNotify)
	    m_pkNotify = new PkNotify(this);
	m_pkNotify->displayUpdates();
    }
    if ( args->isSet("find-file") ) {
	kDebug() << "Hello";
	kDebug() << args->getOption("find-file");
    }
    args->clear();
    return 0;
}


}

#include "kpk.moc"
