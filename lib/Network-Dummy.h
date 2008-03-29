#ifndef NETWORKDUMMY_H
#define NETWORKDUMMY_H

#include "Network.h"

namespace PackageKit {

class NetworkDummy : public Network {

	Q_OBJECT

public:
	NetworkDummy(QObject *parent = 0);
	~NetworkDummy();

	virtual bool isOnline() { return true;};
};

} // End namespace PackageKit

#endif
