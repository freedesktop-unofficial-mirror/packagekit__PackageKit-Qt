#include <QtCore>

extern "C" {
#include <pk-job-list.h>
}

namespace PackageKit {

class JobList : public QObject {

	Q_OBJECT

public:
	JobList(QObject *parent = 0);

	bool refresh();
	bool print();
	QList<QString> get_latest();

public slots:
	void __emit_changed();

signals:
	void changed();

private:
	PkJobList *jobList;

};

}

void __PackageKit_transaction_list_changed(PackageKit::JobList*);
