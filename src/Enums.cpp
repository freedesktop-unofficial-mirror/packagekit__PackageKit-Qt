#include "Enums.h"
#include "utils.h"

namespace PackageKit {

namespace Update {
	UpdateEnum fromString(QString update) {
		return (UpdateEnum)pk_update_enum_from_text(QString2constStr(update));
	}

	QString toString(UpdateEnum update) {
		return QString((char*)pk_update_enum_to_text((PkUpdateEnum)update));
	}
}

namespace Frequence {
	FreqEnum fromString(QString freq) {
		return (FreqEnum)pk_freq_enum_from_text(QString2constStr(freq));
	}

	QString toString(FreqEnum freq) {
		return QString((char*)pk_freq_enum_to_text((PkFreqEnum)freq));
	}
}

namespace Exit {
	ExitEnum fromString(QString exit) {
		return (ExitEnum)pk_exit_enum_from_text(QString2constStr(exit));
	}

	QString toString(ExitEnum exit) {
		return QString((char*)pk_exit_enum_to_text((PkExitEnum)exit));
	}
}

namespace Status {
	StatusEnum fromString(QString status) {
		return (StatusEnum)pk_status_enum_from_text(QString2constStr(status));
	}

	QString toString(StatusEnum status) {
		return QString((char*)pk_status_enum_to_text((PkStatusEnum)status));
	}
}

namespace Role {
	RoleEnum fromString(QString role) {
		return (RoleEnum)pk_role_enum_from_text(QString2constStr(role));
	}

	QString toString(RoleEnum role) {
		return QString((char*)pk_role_enum_to_text((PkRoleEnum)role));
	}
}

namespace Restart {
	RestartEnum fromString(QString restart) {
		return (RestartEnum)pk_restart_enum_from_text(QString2constStr(restart));
	}

	QString toString(RestartEnum restart) {
		return QString((char*)pk_restart_enum_to_text((PkRestartEnum)restart));
	}
}

namespace Group {
	GroupEnum fromString(QString group) {
		return (GroupEnum)pk_group_enum_from_text(QString2constStr(group));
	}

	QString toString(GroupEnum group) {
		return QString((char*)pk_group_enum_to_text((PkGroupEnum)group));
	}
}

namespace Filter {
	FilterEnum fromString(QString filter) {
		return (FilterEnum)pk_filter_enum_from_text(QString2constStr(filter));
	}

	QString toString(FilterEnum filter) {
		return QString((char*)pk_filter_enum_to_text((PkFilterEnum)filter));
	}
}

}
