#include <QtCore>

extern "C" {
#include <pk-task-list.h>
}

namespace PackageKit {

//! Wraps the PkTaskList class
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
	//! Emitted when the list changes
	void changed();
	//! Emitted when a task is finished
	//! \param role Is it an install/update/...
	//! \param id The package id
	//! \param runtime ...
	void finished(unsigned int role, QString id, unsigned int runtime);
	//! Emitted when an error happens
	//! \param role Is it an install/update/...
	//! \param id The package id
	void error(unsigned int role, QString id);

private:
	PkTaskList *taskList;

};

}

void __PackageKit_task_list_changed(PackageKit::TaskList*);
void __PackageKit_task_list_finished(guint, gchar*, guint, PackageKit::TaskList*);
void __PackageKit_error_code(guint, gchar*, PackageKit::TaskList*);
