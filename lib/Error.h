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

#ifndef ERROR_H
#define ERROR_H

#include <QtCore>

#include "Enum.h"

namespace PackageKit {

class Error : public QObject {

	Q_OBJECT
	Q_ENUMS(Value)

public:
typedef enum {
	Oom,
	No_network,
	Not_supported,
	Internal_error,
	Gpg_failure,
	Package_id_invalid,
	Package_not_installed,
	Package_not_found,
	Package_already_installed,
	Package_download_failed,
	Group_not_found,
	Group_list_invalid,
	Dep_resolution_failed,
	Filter_invalid,
	Create_thread_failed,
	Transaction_error,
	Transaction_cancelled,
	No_cache,
	Repo_not_found,
	Cannot_remove_system_package,
	Process_kill,
	Failed_initialization, // Emitted when renewTid fails
	Failed_finalise,
	Failed_config_parsing,
	Cannot_cancel,
	Cannot_getLock,
	No_packages_to_update,
	Cannot_write_repo_config,
	Local_install_failed,
	Bad_gpg_signature,
	Missing_gpg_signature,
	Cannot_install_source_package,
	Repo_configuration_error,
	No_license_agreement,
	File_conflicts,
	Repo_not_available,
	Invalid_package_file,
	Package_install_blocked,
	Package_corrupt,
	Unknown
} Value;

};

} // End namespace PackageKit

#endif
