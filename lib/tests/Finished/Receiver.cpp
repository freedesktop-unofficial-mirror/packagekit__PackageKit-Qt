#include "Receiver.h"

using namespace PackageKit;

Receiver::Receiver(QObject *parent) : QObject(parent) {

}

void Receiver::callback(Exit::Value v, uint runtime) {
	qDebug() << "Finished with status" << EnumToString<Exit>(v)<< "in" << runtime << "milliseconds";
}
