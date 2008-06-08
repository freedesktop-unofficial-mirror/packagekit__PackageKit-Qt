#ifndef SIGNATURETYPE_H
#define SIGNATURETYPE_H

#include <QtCore>

#include "Enum.h"

namespace PackageKit {

class SignatureType : public QObject {

	Q_OBJECT
	Q_ENUMS(Value)

public:
	enum Value {
		Gpg,
		Unknown
	};
};

} // End namespace PackageKit

#endif
