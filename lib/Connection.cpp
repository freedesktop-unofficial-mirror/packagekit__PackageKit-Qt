#include "Connection.h"


using namespace PackageKit;

//! Creates a new Connection object (equivalent to pk_connection_new)
//! \param parent the parent object, or NULL
Connection::Connection (QObject *parent) : QObject(parent) {
	connection = pk_connection_new();
	g_signal_connect(connection, "connection-changed", G_CALLBACK(__PackageKit_connection_changed), this);
}

//! Tests if the connection is valid
//! \return TRUE if the connection is valid, FALSE else
bool Connection::valid() {
	return pk_connection_valid(connection);
}

void Connection::__emit_changed(bool b) {
	emit changed(b);
}

void __PackageKit_connection_changed(bool b, Connection *instance) {
	instance->__emit_changed(b);
}
