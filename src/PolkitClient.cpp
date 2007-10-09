#include "PolkitClient.h"
#include "Error.h"
#include "utils.h"

using namespace PackageKit;

PolkitClient::PolkitClient(QObject *parent) : QObject(parent) {
	client = pk_polkit_client_new();
}

bool PolkitClient::gain_privilege(QString action) {
	return pk_polkit_client_gain_privilege(client, QString2constStr(action));
}

bool PolkitClient::gain_privilege_str(QString error_str) {
	return pk_polkit_client_gain_privilege_str(client, QString2constStr(error_str));
}

bool PolkitClient::client_error_denied_by_policy(Error *error) {
	return pk_polkit_client_error_denied_by_policy(error->toGError());
}
