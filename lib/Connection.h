#include <QtDBus>
#include "DBusProxy.h"

#define PK_PATH "/org/freedesktop/PackageKit"

namespace PackageKit {

class Connection : public QObject {
	
	Q_OBJECT

public:
	Connection(QObject *parent = 0);
	~Connection();

	bool valid();

signals:
	// Changed can not be implemented, as Qt does not notify us of connections/disconnections...

private:
	DBusProxy *proxy;
};

} // End namespace PackageKit
