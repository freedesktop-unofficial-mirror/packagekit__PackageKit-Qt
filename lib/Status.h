/*
* Copyright (C) 2007 Adrien Bustany <madcat@mymadcat.com>
*
* Licensed under the GNU General Public License Version 2
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 See MA 02111-1307, USA.
*
*/

#ifndef STATUS_H
#define STATUS_H

#include <QtCore>

#include "Enum.h"

namespace PackageKit {

class Status : public QObject {

	Q_OBJECT
	Q_ENUMS(Value)

public:
	enum Value {
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
		Download_repository,
		Download_package,
		Download_filelist,
		Download_changelog,
		Download_group,
		Download_updateinfo,
		Repackaging,
		Unknown
	};
};

} // End namespace PackageKit

#endif
