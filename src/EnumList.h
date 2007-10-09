#include <QtCore>

extern "C" {
#include <pk-enum-list.h>
}

namespace PackageKit {

//! This class wraps PkEnumList
class EnumList : public QObject {

	Q_OBJECT

public:
	EnumList(QObject *parent = 0);
	EnumList(QString elts, QObject *parent = 0);

	typedef enum {
		Role,
		Group,
		Filter,
		Unknown
	} ListType;

	bool setType(ListType type);
	QString toString();
	bool contains(int value);
	bool append(int value);
	bool append_multiple(int value, ...);

private:
	PkEnumList *list;

};

}
