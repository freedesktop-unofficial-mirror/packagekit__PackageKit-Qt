#include <QtCore>

extern "C" {
#include <pk-polkit-client.h>
}

namespace PackageKit {

class Error;

class PolkitClient : public QObject {

	Q_OBJECT

public:
	PolkitClient(QObject *parent = 0);

	bool gain_privilege(QString action);
	bool gain_privilege_str(QString error_str);
	bool client_error_denied_by_policy(Error *error);

private:
	PkPolkitClient *client;

};

}
