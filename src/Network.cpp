#include "Network.h"

using namespace PackageKit;

//! Creates a new Network object (equivalent to pk_network_new)
//! \param parent the parent object, or NULL
Network::Network(QObject *parent) : QObject(parent) {
	network = pk_network_new();
	g_signal_connect(network, "online", G_CALLBACK(__PackageKit_online), this);
}

//! Checks if the network is online or not (equivalent to pk_network_is_online)
//! \return TRUE if the host is connected to a network, FALSE else
bool Network::is_online() {
	return pk_network_is_online(network);
}

void Network::__emit_online(bool b) {
	emit online(b);
}

void __PackageKit_online(bool b, PackageKit::Network *n) {
	n->__emit_online(b);
}
