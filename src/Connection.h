#include <QtCore>

extern "C" {
#include <pk-connection.h>
}

namespace PackageKit {


//! This class wraps PkConnection
class Connection : public QObject {

	Q_OBJECT

public:
	Connection(QObject *parent = 0);

	bool valid();

public slots:
	void __emit_changed(bool);

signals:
	//! Emitted when the state of the connection changes
	void changed(bool);

private:
	PkConnection *connection;

};


}

// Glib signal proxies
void __PackageKit_connection_changed(bool, PackageKit::Connection*);
