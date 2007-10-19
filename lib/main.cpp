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
