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

#ifndef GROUPS_H
#define GROUPS_H

#include <QtCore>

#include "Enum.h"

namespace PackageKit {

class Groups : public QObject {

	Q_OBJECT
	Q_ENUMS(Value)

public:
typedef enum {
	Accessibility		= 1 << 0,
	Accessories		= 1 << 1,
	Admin_tools		= 1 << 2,
	Communication		= 1 << 3,
	Desktop_gnome		= 1 << 4,
	Desktop_kde		= 1 << 5,
	Desktop_other		= 1 << 6,
	Desktop_xfce		= 1 << 7,
	Education		= 1 << 8,
	Fonts			= 1 << 9,
	Games			= 1 << 10,
	Graphics		= 1 << 11,
	Internet		= 1 << 12,
	Legacy			= 1 << 13,
	Localization		= 1 << 14,
	Maps			= 1 << 15,
	Multimedia		= 1 << 16,
	Network			= 1 << 17,
	Office			= 1 << 18,
	Other			= 1 << 19,
	Power_management	= 1 << 20,
	Programming		= 1 << 21,
	Publishing		= 1 << 22,
	Repos			= 1 << 23,
	Security		= 1 << 24,
	Servers			= 1 << 25,
	System			= 1 << 26,
	Virtualization		= 1 << 27,
	Unknown			= 1 << 28
} Value;

};

} // End namespace PackageKit

#endif
