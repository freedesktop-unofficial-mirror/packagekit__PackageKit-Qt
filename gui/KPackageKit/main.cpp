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

#include "kpk.h"
#include <KDebug>
#include <KConfig>
#include <KLocale>

#include <KUrl>
#include <KLocale>
#include <KAboutData>
#include <KCmdLineArgs>

int main(int argc, char **argv)
{
	// ignore SIGPIPE and SIGXFSZ
// 	signal(SIGPIPE,SIG_IGN);
// 	signal(SIGXFSZ,SIG_IGN);
	
// 	bt::SetClientInfo("KPackageKit",kt::MAJOR,kt::MINOR,kt::RELEASE,bt::NORMAL,"KT");
	
	KAboutData about(
		"KPackageKit", 0, ki18n("KPackageKit"),
		"0.1", ki18n("PackageKit Interface for KDE"),
		KAboutData::License_GPL, 
		ki18n("(C) 2008 Daniel Nicoletti"), 
		KLocalizedString(),
		"http://www.packagekit.org/");

	about.addAuthor(ki18n("Daniel Nicoletti"), KLocalizedString(), "dantti85-pk@yahoo.com.br","http://www.packagekit.org" );

	about.addCredit(ki18n("Adrien Bustany"),	ki18n("libpackagekit-qt and other stuff"),"@");

	KCmdLineArgs::init(argc, argv, &about);

	KCmdLineOptions options;
	options.add( "find-file <file>", ki18n("Finds the Package Containing the file") );
	options.add( "smart-icon", ki18n("Shows the Smart Icon Transactions") );
	options.add( "show-updates", ki18n("Displays Updates") );
	KCmdLineArgs::addCmdLineOptions(options);
	
	kpackagekit::Kpk::addCmdLineOptions();
	if (!kpackagekit::Kpk::start())
	{
		kDebug() << "kpackagekit is already running !";
		return 0;
	}

	kpackagekit::Kpk app;
	app.exec();
	return 0;
}




