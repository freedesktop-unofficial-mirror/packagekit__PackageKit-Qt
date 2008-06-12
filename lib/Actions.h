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

#ifndef ACTIONS_H
#define ACTIONS_H

#include <QtCore>

#include "Enum.h"

namespace PackageKit {

class Actions : public QObject {

	Q_OBJECT
	Q_ENUMS(Value)

public:
typedef enum {
	Cancel				= 1 << 0,
	Get_depends			= 1 << 1,
	Get_details			= 1 << 2,
	Get_files			= 1 << 3,
	Get_repo_list		= 1 << 4,
	Get_requires		= 1 << 5,
	Get_update_detail	= 1 << 6,
	Get_updates			= 1 << 7,
	Install_files		= 1 << 8,
	Install_package		= 1 << 9,
	Refresh_cache		= 1 << 10,
	Remove_packages		= 1 << 11,
	Repo_enable			= 1 << 12,
	Repo_set_data		= 1 << 13,
	Resolve				= 1 << 14,
	Search_details		= 1 << 15,
	Search_file			= 1 << 16,
	Search_group		= 1 << 17,
	Search_name			= 1 << 18,
	Update_package		= 1 << 19,
	Update_system		= 1 << 20,
	What_provides		= 1 << 21
} Value;

};

} // End namespace PackageKit

#endif
