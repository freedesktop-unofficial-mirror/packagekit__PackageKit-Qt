#include "PolkitClient.h"
#include "Error.h"
#include "utils.h"

using namespace PackageKit;

//! Creates a new PolkitClient object (equivalent to pk_polkit_client_new)
//! \param parent the parent object, or NULL
PolkitClient::PolkitClient(QObject *parent) : QObject(parent) {
	client = pk_polkit_client_new();
}

//! Tries to gain privileges to exectute the specified action (equivalent to pk_polkit_client_gain_privilege)
//! \param action The action to gain privileges for
//! \return TRUE if succeeded, FALSE else
bool PolkitClient::gain_privilege(QString action) {
	return pk_polkit_client_gain_privilege(client, QString2constStr(action));
}

//! Equivalent to pk_polkit_client_gain_privilege_str
bool PolkitClient::gain_privilege_str(QString error_str) {
	return pk_polkit_client_gain_privilege_str(client, QString2constStr(error_str));
}

//! Checks if the client has been denied by a policy
//! \param error The error returned
//! \return TRUE if the error is a "denied by policy" error, FALSE else
bool PolkitClient::client_error_denied_by_policy(Error *error) {
	return pk_polkit_client_error_denied_by_policy(error->toGError());
}
