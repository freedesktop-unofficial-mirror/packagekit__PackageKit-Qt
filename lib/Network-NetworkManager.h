#ifndef NETWORK_NETWORKMANAGER_H
#define NETWORK_NETWORKMANAGER_H

#include <QDBusInterface>
#include "Network.h"

namespace PackageKit {

class NetworkNetworkManager : public Network {

	Q_OBJECT

public:
	NetworkNetworkManager(QObject *parent = 0);
	~NetworkNetworkManager();

	virtual bool isOnline();
public signals:
	virtual void online(bool status);
private:
	QDBusInterface *netwokManager;
};

} // End namespace PackageKit

#endif
