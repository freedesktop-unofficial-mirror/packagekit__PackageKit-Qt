/*
 * Copyright (C) 2007 Adrien Bustany <madcat@mymadcat.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#include <QApplication>
#include <QtCore>

#include "QPackageKitInterface.h"

#define PK_DBUS_SERVICE "org.freedesktop.PackageKit"
#define PK_DBUS_PATH "/org/freedesktop/PackageKit"

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	QPackageKitInterface iface(PK_DBUS_SERVICE, PK_DBUS_PATH, QDBusConnection::systemBus());
	QDBusReply<QString> reply = iface.GetTid();
	if(reply.isValid()) qDebug() << "Appel valide, valeur de retour " << reply.value();
	else qDebug() << "invalide";
	return app.exec();
}
