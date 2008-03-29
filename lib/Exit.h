#ifndef EXIT_H
#define EXIT_H

#include <QtCore>

#include "Enum.h"

namespace PackageKit {

class Exit : public QObject {

	Q_OBJECT
	Q_ENUMS(Value)

public:
typedef enum {
	Success,
	Failed,
	Quit,
	Kill,
	Unknown
} Value;

};

} // End namespace PackageKit

#endif
