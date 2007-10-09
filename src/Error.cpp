#include "Error.h"
#include "utils.h"

using namespace PackageKit;

Error::Error(GError *error) {
	_domain = error->domain;
	_code = error->code;
	_message = QString(error->message);
}

int Error::domain() { return _domain; };
int Error::code() { return _code; }
QString Error::message() { return _message; }

GError* Error::toGError() {
	GError *error = g_error_new(_domain, _code, "%s", QString2constStr(_message));
	return error;
}

Error::ErrorCodeEnum Error::fromString(QString error) {
	return (Error::ErrorCodeEnum)pk_error_enum_from_text(QString2constStr(error));
}

QString Error::toString(Error::ErrorCodeEnum error) {
	return QString((char*)pk_error_enum_to_text((PkErrorCodeEnum)error));
}
