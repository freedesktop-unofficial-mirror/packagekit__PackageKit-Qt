#include <QtCore>

#include "../../Status.h"

using namespace PackageKit;

int main(int argc, char **argv) {
	qDebug() << "Value of Status::Setup is " << EnumFromString<Status>("Setup");
	qDebug() << "Status::Install has text value " << EnumToString<Status>((int)Status::Install);
}
