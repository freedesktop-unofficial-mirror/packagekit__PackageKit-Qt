#include <QtCore>

extern "C" {
#include <pk-network.h>
}

namespace PackageKit {

//! Wraps the PkNetwork class
class Network : public QObject {

	Q_OBJECT

public:
	Network(QObject *parent = 0);

	bool is_online();

public slots:
	void __emit_online(bool);

signals:
	//! Emitted when the host connects to/disconnects from a network
	//! \param connected TRUE if the host is connected, FALSE else
	void online(bool connected);

private:
	PkNetwork *network;

};

}

void __PackageKit_online(bool, PackageKit::Network*);
