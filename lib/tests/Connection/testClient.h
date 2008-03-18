#include <QtCore>

#include "../../Connection.h"

using namespace PackageKit;

class testClient : public QObject {

	Q_OBJECT

public:
	testClient(QObject *parent = 0);

public slots:
	void pkChanged(bool status);

private:
	Connection *con;

};
