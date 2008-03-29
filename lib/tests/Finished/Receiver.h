#ifndef RECEIVER_H
#define RECEIVER_H

#include <QtCore>
#include "../../Exit.h"

using namespace PackageKit;

class Receiver : public QObject {

	Q_OBJECT

public:
	Receiver(QObject *parent = 0);

public slots:
	void callback(Exit::Value v, uint runtime);

};

#endif
