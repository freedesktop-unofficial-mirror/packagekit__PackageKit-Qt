#include "TaskList.h"

using namespace PackageKit;

TaskList::TaskList(QObject *parent) : QObject(parent) {
	taskList = pk_task_list_new();
}

bool TaskList::refresh() {
	return pk_task_list_refresh(taskList);
}

bool TaskList::print() {
	return pk_task_list_print(taskList);
}

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
