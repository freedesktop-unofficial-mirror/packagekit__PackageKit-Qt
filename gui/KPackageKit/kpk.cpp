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
#include "PkNotify.h"

namespace kpackagekit {

Kpk::Kpk() : KUniqueApplication()
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
//     kt::GUI *widget = 0; 
//     if (!main_widget)
//     {
//         bt::InitLog(kt::DataDir() + "log",true);
// 	setQuitOnLastWindowClosed(false);
// 	widget = new kt::GUI();
// 	setTopWidget(widget);
// 	main_widget = widget;
//     }
//     else
//     {
// 	widget = main_widget;
// 	widget->show();
//     }
// 
//     if (widget)

//     {

// KNotify no;
// QStringList a;
// a << "one" << "two";
	for (int i = 0; i < args->count(); i++)
	{
		if ( args->isSet("silent") )
			kDebug() << "Hello";
		else if ( args->isSet("show-updates") ) {
		    kDebug() << "Hi mostra!";
		    PkNotify *a = new PkNotify(this);
		    a->displayUpdates();
		}
		else {
// 		    kDebug() << "Hi something!";
		}
		
	}
//     }
    args->clear();
    return 0;
}


}

#include "kpk.moc"
