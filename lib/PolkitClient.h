#ifndef POLKITCLIENT_H
#define POLKITCLIENT_H

#include <QtCore>

namespace PackageKit {

class PolkitClient : QObject{

	Q_OBJECT

public:
	PolkitClient(QObject *parent = 0);
	bool getAuth(const QString& action);
private:

};

} // End namespace PackageKit

#endif
