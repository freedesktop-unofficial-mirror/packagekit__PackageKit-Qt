#include "JobList.h"

using namespace PackageKit;

JobList::JobList(QObject *parent) : QObject(parent) {
	jobList = pk_job_list_new();
}

bool JobList::refresh() {
	return pk_job_list_refresh(jobList);
}

bool JobList::print() {
	return pk_job_list_print(jobList);
}

QList<QString> JobList::get_latest() {
	QList<QString> list;

	const gchar **array = pk_job_list_get_latest(jobList);
	guint length = g_strv_length((gchar**)array);

	for(guint i = 0 ; i < length ; ++i) {
		list.append(QString(array[i]));
	}

	return list;
}

void JobList::__emit_changed() {
	emit changed();
}

void __PackageKit_transaction_list_changed(JobList *l) {
	l->__emit_changed();
}
