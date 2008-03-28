#ifndef STATUS_H
#define STATUS_H

#include <QtCore>

#include "Enum.h"

namespace PackageKit {

class Status : public QObject {

	Q_OBJECT
	Q_ENUMS(Value)

public:
	static const enum {
		Setup,
		Wait,
		Query,
		Info,
		Remove,
		Refresh_cache,
		Download,
		Install,
		Update,
		Cleanup,
		Obsolete,
		Dep_resolve,
		Rollback,
		Commit,
		Request,
		Finished,
		Cancel,
		Unknown
	} Value;
};

} // End namespace PackageKit

#endif
