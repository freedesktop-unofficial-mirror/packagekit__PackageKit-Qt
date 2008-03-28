#ifndef NETWORKDUMMY_H
#define NETWORKDUMMY_H

#include "Network.h"

namespace PackageKit {

class NeworkDummy : public Network {

	Q_OBJECT

public:
	NeworkDummy(QObject *parent = 0);
	~NeworkDummy();

	virtual bool isOnline() { return true;};
};

} // End namespace PackageKit

#endif
