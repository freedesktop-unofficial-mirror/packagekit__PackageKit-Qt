#include "testClient.h"

testClient::testClient (QObject *parent) : QObject(parent) {
	con = new Connection(this);
	if(con->valid()) qDebug() << "PK is running";
	connect(con, SIGNAL(changed(bool)), this, SLOT(pkChanged(bool)));
}

void testClient::pkChanged(bool status) {
	qDebug() << "PK is now" << (status ? "running" : "stopped");
}
