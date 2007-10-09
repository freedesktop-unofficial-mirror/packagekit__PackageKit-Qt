#include <QtCore>

extern "C" {
#include <pk-task-list.h>
}

namespace PackageKit {

class TaskList : public QObject {

	Q_OBJECT

public:
	TaskList(QObject *parent = 0);

	bool refresh();
	bool print();
	QList<void*> get_latest();

public slots:
	void __emit_changed();
	void __emit_finished(unsigned int, QString, unsigned int);
	void __emit_error(unsigned int, QString);

signals:
	void changed();
	void finished(unsigned int, QString, unsigned int);
	void error(unsigned int, QString);

private:
	PkTaskList *taskList;

};

}

void __PackageKit_task_list_changed(PackageKit::TaskList*);
void __PackageKit_task_list_finished(guint, gchar*, guint, PackageKit::TaskList*);
void __PackageKit_error_code(guint, gchar*, PackageKit::TaskList*);
