/*
* Copyright (C) 2007 Adrien Bustany <madcat@mymadcat.com>
* Copyright (C) 2008 Daniel Nicoletti <dantti85-pk@yahoo.com.br>
*
* Licensed under the GNU General Public License Version 2
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 See MA 02111-1307, USA.
*
*/

#ifndef INFO_H
#define INFO_H

#include <QtCore>

#include "Enum.h"

namespace PackageKit {

class Info : public QObject {

	Q_OBJECT
	Q_ENUMS(Value)

public:
typedef enum {
	Installed,
	Available,
	Low,
	Normal,
	Important,
	Security,
	Bugfix,
	Enhancement,
	Blocked,
	Downloading,
	Updating,
	Installing,
	Removing,
	Cleanup,
	Obsoleting,
	Unknown
} Value;

};

} // End namespace PackageKit

#endif
