#include "EnumList.h"
#include "utils.h"

using namespace PackageKit;

//! Creates an empty EnumList (equivalent to pk_enum_list_new)
//! \param parent the parent object, or NULL
EnumList::EnumList(QObject *parent) : QObject(parent) {
	list = pk_enum_list_new();
}

//! Creates an EnumList, and fills it with elts (equivalent to pk_enum_list_from_string)
//! \param elts The elements to fill the list with
//! \param parent the parent object, or NULL
EnumList::EnumList(QString elts, QObject *parent) : QObject(parent) {
	list = pk_enum_list_new();
	if(!pk_enum_list_from_string(list, QString2constStr(elts)))
		qFatal("Error : pk_enum_list_from_string failed");
}

//! Sets the type of the list (equivalent to pk_enum_list_set_type)
//! \param type The type of the list
bool EnumList::setType(ListType type) {
	return pk_enum_list_set_type(list, (PkEnumListType)type);
}

//! Returns the EnumList as a string (equivalent to pk_enum_list_to_string)
//!
QString EnumList::toString() {
	return QString(pk_enum_list_to_string(list));
}

//! Looks for value in the list (equivalent to pk_enum_list_contains)
//! \param value The value to look for
//! \return TRUE if found, FALSE else
bool EnumList::contains(int value) {
	return pk_enum_list_contains(list, value);
}

//! Appends an element to the list (equivalent of pk_enum_list_append)
//! \param value The value to append to the list
//! \return TRUE if value has been added, FALSE else
bool EnumList::append(int value) {
	return pk_enum_list_append(list, value);
}

//! Appends multiple elements to the list (equivalent of pk_enum_list_append_multiple)
//! \param value, ... A NULL terminated list of values
//! \return TRUE if values have been added, FALSE else
bool EnumList::append_multiple(int value, ...) {
	va_list ap;
	va_start(ap, value);
	int i;

	while((i = va_arg(ap, int))) {
		if(!append(i)) return false;
	}

	va_end(ap);

	return true;
}
