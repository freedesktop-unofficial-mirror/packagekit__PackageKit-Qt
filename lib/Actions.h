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
	Get_repo_list			= 1 << 4,
	Get_requires			= 1 << 5,
	Get_packages			= 1 << 6,
	Get_update_detail		= 1 << 7,
	Get_updates			= 1 << 8,
	Install_files			= 1 << 9,
	Install_packages		= 1 << 10,
	Refresh_cache			= 1 << 11,
	Remove_packages			= 1 << 12,
	Repo_enable			= 1 << 13,
	Repo_set_data			= 1 << 14,
	Resolve				= 1 << 15,
	Search_details			= 1 << 16,
	Search_file			= 1 << 17,
	Search_group			= 1 << 18,
	Search_name			= 1 << 19,
	Update_package			= 1 << 20,
	Update_system			= 1 << 21,
	What_provides			= 1 << 22
} Value;

};

} // End namespace PackageKit

#endif
