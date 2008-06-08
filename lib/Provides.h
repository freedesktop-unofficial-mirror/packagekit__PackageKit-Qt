#ifndef PROVIDES_H
#define PROVIDES_H

#include <QtCore>

#include "Enum.h"

namespace PackageKit {

class Provides : public QObject {

	Q_OBJECT
	Q_ENUMS(Value)

public:
	enum Value {
		Any,
		Modalias,
		Codec,
		Mimetype,
		Unknown
	};
};

} // End namespace PackageKit

#endif
