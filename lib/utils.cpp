#include "utils.h"

const gchar* QString2constStr (QString str) {
	return str.toAscii().constData();
}

