#ifndef NETWORK_H
#define NETWORK_H

#include <QtCore>

namespace PackageKit {

class Network : public QObject {

	Q_OBJECT

public:
	Network(QObject *parent = 0);
	~Network();

	bool isOnline();
public signals:
	void online(bool arg1); 
};

} // End namespace PackageKit

#endif
