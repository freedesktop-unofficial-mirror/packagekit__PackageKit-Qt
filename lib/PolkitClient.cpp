#include <polkit-dbus/polkit-dbus.h>

#include "PolkitClient.h"
#include "constants.h"

using namespace PackageKit;

PolkitClient::PolkitClient(QObject *parent) : QObject(parent) {
}

bool PolkitClient::getAuth(const QString &action) {
	DBusError e;
	dbus_error_init(&e);

	bool auth = polkit_auth_obtain(action.toAscii().data(), 0, QCoreApplication::applicationPid(), &e);
	if(!auth) {
		qDebug() << "Authentification error :" << e.name << ":" << e.message;
	}
    
	return auth;
}

