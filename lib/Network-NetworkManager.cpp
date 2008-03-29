#include "Network-NetworkManager.h"

namespace PackageKit {

NetworkNetworkManager::NetworkNetworkManager(QObject *parent) : QObject(parent)
{
	netwokManager = new netwokManager();
}

NetworkNetworkManager::~NetworkNetworkManager()
{
	delete netwokManager;
}

} // End namespace PackageKit
