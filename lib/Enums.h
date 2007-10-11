#include <QtCore>

extern "C" {
#include <pk-enum.h>
}

//! This namespace contains all the PackageKit related functions and enums
namespace PackageKit {

//! Contains the Role enum (equivalent to PkRoleEnum)
namespace Role {
	/* what we asked to do */
	typedef enum {
		Cancel,
		Resolve,
		Get_depends,
		Get_update_detail,
		Get_description,
		Get_requires,
		Get_updates,
		Search_details,
		Search_file,
		Search_group,
		Search_name,
		Refresh_cache,
		Update_system,
		Remove_package,
		Install_package,
		Install_file,
		Update_package,
		Unknown
	} RoleEnum;

	static RoleEnum fromString(QString status);
	static QString toString(RoleEnum status);
};

//! Contains the Status enum (equivalent to PkStatusEnum)
namespace Status {
	/* what we are actually doing */
	typedef enum {
		Setup,
		Wait,
		Query,
		Remove,
		Refresh_cache,
		Download,
		Install,
		Update,
		Unknown
	} StatusEnum;

	static StatusEnum fromString(QString status);
	static QString toString(StatusEnum status);
};

//! Contains the Exit enum (equivalent to PkExitEnum)
namespace Exit {
	typedef enum {
		Success,
		Failed,
		Canceled,
		Unknown
	} ExitEnum;

	static ExitEnum fromString(QString exit);
	static QString toString(ExitEnum exit);
};

//! Contains the Filter enum (equivalent to PkFilterEnum)
namespace Filter {
	typedef enum {
		Development,
		Installed,
		Gui,
		Unknown
	} FilterEnum;

	static FilterEnum fromString(QString filter);
	static QString toString(FilterEnum filter);
};

//! Contains the Restart enum (equivalent to PkRestartEnum)
namespace Restart {
	typedef enum {
		Restart_enum_none,
		Restart_enum_application,
		Restart_enum_session,
		Restart_enum_system
	} RestartEnum;

	static RestartEnum fromString(QString restart);
	static QString toString(RestartEnum restart);
};

// Enum ErrorCodeNum is in Error.h

//! Contains the Role enum (equivalent to PkRoleEnum)
namespace Group {
	typedef enum {
		Accessibility,
		Accessories,
		Education,
		Games,
		Graphics,
		Internet,
		Office,
		Other,
		Programming,
		Multimedia,
		System,
		Unknown
	} GroupEnum;

	static GroupEnum fromString(QString group);
	static QString toString(GroupEnum group);
};

//! Contains the Frequence enum (equivalent to PkFreqEnum)
namespace Frequence {
	typedef enum {
		Hourly,
		Daily,
		Weekly,
		Never,
		Unknown
	} FreqEnum;

	static FreqEnum fromString(QString freq);
	static QString toString(FreqEnum freq);
};

//! Contains the Update enum (equivalent to PkUpdateEnum)
namespace Update {
	typedef enum {
		All,
		Security,
		None,
	} UpdateEnum;

	static UpdateEnum fromString(QString update);
	static QString toString(UpdateEnum update);
}

} // PackageKit namespace
