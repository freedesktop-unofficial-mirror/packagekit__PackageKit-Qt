#ifndef RESTART_H
#define RESTART_H

#include <QtCore>

#include "Enum.h"

namespace PackageKit {

class Restart: public QObject {

	Q_OBJECT
	Q_ENUMS(Value)

public:
	enum Value {
		None,
		Application,
		Session,
		System,
		Unknown
	};
};

} // End namespace PackageKit

#endif
