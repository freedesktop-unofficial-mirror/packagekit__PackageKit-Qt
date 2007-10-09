#include <QtCore>

extern "C" {
#include <pk-network.h>
}

namespace PackageKit {

class Network : public QObject {

	Q_OBJECT

public:
	Network(QObject *parent = 0);

	bool is_online();

public slots:
	void __emit_online(bool);

signals:
	void online(bool);

private:
	PkNetwork *network;

};

}

void __PackageKit_online(bool, PackageKit::Network*);
