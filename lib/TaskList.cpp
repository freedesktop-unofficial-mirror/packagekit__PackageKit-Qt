#include "TaskList.h"

using namespace PackageKit;

//! Creates a new TaskList object (equivalent to pk_task_list_new)
//! \param parent the parent object, or NULL
TaskList::TaskList(QObject *parent) : QObject(parent) {
	taskList = pk_task_list_new();
}

//! Refreshes the task list (equivalent to pk_task_list_refresh)
//! \return TRUE if succeeded, FALSE else
bool TaskList::refresh() {
	return pk_task_list_refresh(taskList);
}

//! Prints the task list (equivalent to pk_task_list_print)
//! \return TRUE if succeded, FALSE else
bool TaskList::print() {
	return pk_task_list_print(taskList);
}

//! Gets the latest task list (equivalent to pk_task_list_get_latest)
//! \return A list of strings, each string holding a task id
QList<void*> TaskList::get_latest() {
	QList<void*> list;

	GPtrArray *array = pk_task_list_get_latest(taskList);

	for(guint i = 0 ; i < array->len ; ++i) {
		list.append(array->pdata[i]);
	}

	return list;
}

void TaskList::__emit_changed() {
	emit changed();
}

void TaskList::__emit_finished(unsigned int a, QString b, unsigned int c) {
	emit finished(a, b, c);
}

void TaskList::__emit_error(unsigned int a, QString b) {
	emit error(a, b);
}

void __PackageKit_transaction_list_changed(TaskList *l) {
	l->__emit_changed();
}

void __PackageKit_task_list_finished(unsigned int a, gchar *b, unsigned int c, TaskList *l) {
	l->__emit_finished(a, QString(b), c);
}

void __PackageKit_error_code(unsigned int a, gchar *b, TaskList *l) {
	l->__emit_error(a, QString(b));
}
