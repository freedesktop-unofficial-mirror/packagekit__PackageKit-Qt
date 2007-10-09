#include <QtCore>

extern "C" {
#include <glib.h>
#include <pk-enum.h>
}

namespace PackageKit {

class Error {

public:
	Error(GError *error);

	int domain();
	int code();
	QString message();
	GError *toGError();

	typedef enum {
		Oom,
		No_network,
		Not_supported,
		Internal_error,
		Gpg_failure,
		Package_id_invalid,
		Package_not_installed,
		Package_already_installed,
		Package_download_failed,
		Dep_resolution_failed,
		Filter_invalid,
		Create_thread_failed,
		Transaction_error,
		Unknown
	} ErrorCodeEnum;

	static ErrorCodeEnum fromString(QString error);
	static QString toString(ErrorCodeEnum error);


private:
	int _domain;
	int _code;
	QString _message;

};

}
