#include "Error.h"
#include "utils.h"

using namespace PackageKit;

//! Constructs a new Error from an existing GError
//! \param error An existing Gerror
Error::Error(GError *error) {
	_domain = error->domain;
	_code = error->code;
	_message = QString(error->message);
}

//! Returns the error's domain
//! \return Error domain
int Error::domain() { return _domain; };
//! Returns the error's code
//! \return Error code
int Error::code() { return _code; }
//! Returns the error's message
//! \return Error message
QString Error::message() { return _message; }

//! Converts the error back to a GError
//! \return A new GError similar to the object
GError* Error::toGError() {
	GError *error = g_error_new(_domain, _code, "%s", QString2constStr(_message));
	return error;
}

//! Creates an ErrorCodeEnum from a string
//! \param error The string containing the error
//! \return The corresponding ErrorCodeEnum
Error::ErrorCodeEnum Error::fromString(QString error) {
	return (Error::ErrorCodeEnum)pk_error_enum_from_text(QString2constStr(error));
}

//! Converts an ErrorCodeEnum to a string
//! \param error The error to convert
//! \return A string containing the error
QString Error::toString(Error::ErrorCodeEnum error) {
	return QString((char*)pk_error_enum_to_text((PkErrorCodeEnum)error));
}
