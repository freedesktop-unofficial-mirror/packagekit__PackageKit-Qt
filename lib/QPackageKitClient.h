/*
 * Copyright (C) 2007 Adrien Bustany <madcat@mymadcat.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#ifndef QPACKAGEKITCLIENT_H
#define QPACKAGEKITCLIENT_H

#include <QtCore>
#include <QtDBus>

#include "QPackageKitInterface.h"
#include "PkPackage.h"

#define PK_DBUS_SERVICE "org.freedesktop.PackageKit"
#define PK_DBUS_PATH "/org/freedesktop/PackageKit"

//! Controls the PackageKit daemon
/*! This object uses a QPackageKitInterface (generated with qdbusxml2cpp) to control the PackageKit daemon.
It implements all the methods available in libpackagekit
*/
class QPackageKitClient : public QObject {

	Q_OBJECT;

public:
	// Enums
	class Role {
	public:
		static void construct();

		//! What we asked to do
		typedef enum {
			Cancel,
			Resolve,
			Rollback,
			Get_depends,
			Get_update_detail,
			Get_description,
			Get_requires,
			Get_updates,
			Search_details,
			Search_file,
			Search_group,
			Search_name,
			Refresh_cache,
			Update_system,
			Remove_package,
			Install_package,
			Install_file,
			Update_package,
			Get_repo_list,
			Repo_enable,
			Repo_set_data,
			Unknown
		} RoleEnum;
		static QString toString(RoleEnum e);
		static RoleEnum fromString(QString s);

	private:
		static QMap<int, QString> stringValues;
	};

	class Status {
	public:
		static void construct();

		//! What we are doing
		typedef enum {
			Setup,
			Wait,
			Query,
			Remove,
			Refresh_cache,
			Download,
			Install,
			Update,
			Unknown
		} StatusEnum;
		static QString toString(StatusEnum e);
		static StatusEnum fromString(QString s);

	private:
		static QMap<int, QString> stringValues;
	};

	class Exit {
	public:
		static void construct();

		typedef enum {
			Success,
			Failed,
			Canceled,
			Unknown
		} ExitEnum;
		static QString toString(ExitEnum e);
		static ExitEnum fromString(QString s);

	private:
		static QMap<int, QString> stringValues;
	};

	class Filter {
	public:
		static void construct();

		typedef enum {
			Development,
			Installed,               
			Gui,
			Normal,          /* not development */
			Available,       /* not installed */
			Text,            /* not gui */
			Unknown
		} FilterEnum;
		static QString toString(FilterEnum e);
		static FilterEnum fromString(QString s);

	private:
		static QMap<int, QString> stringValues;
	};
	// End Enums

	//! QPackageKitClient constructor
	QPackageKitClient(QObject *parent = 0);

	//! Cancels the current transaction
	void Cancel();

	//! Searches for a package using its name
	bool searchName(QString name, QList<Filter::FilterEnum> filters);

	//! Orders the description of a package
	bool getDescription(QString packageId);
	bool getDescription(PkPackage *p);

	//! Installs a package
	bool installPackage(QString packageId);
	bool installPackage(PkPackage *p);

	//! Removes a package
	bool removePackage(QString packageId);
	bool removePackage(PkPackage *p);

signals:
	//! Emitted when the daemon sends us a package
	void Package(const QString &info, const QString &package_id, const QString &summary);

	//! Emitted when the current transaction is finished
	void Finished(QPackageKitClient::Exit::ExitEnum exitCode, uint runtime);

	//! Emitted when the current transaction's progress changes 
        void ProgressChanged(uint percentage, uint subpercentage, uint elapsed, uint remaining);

	//! Emitted when we cannot track the progress of the current transaction
	void NoProgressUpdates();
	
	//! Emitted when the daemon sends us a package description
	void Description(const QString &package_id, const QString &licence, const QString &group,
				const QString &detail, const QString &url, qulonglong size, const QString &file_list);
	
public slots:
	// All slots prefixed with proxy merely proxy signal from the QPackageKitInterface, stripping the tid after
	// having ensured that the signal concerns our transaction
	void proxy_Package(const QString &thisTid, const QString &info, const QString &package_id, const QString &summary);
	void proxy_Finished(const QString &thisTid, const QString &status, uint runtime);
        void proxy_ProgressChanged(const QString &thisTid, uint percentage, uint subpercentage, uint elapsed, uint remaining);
	void proxy_Description(const QString &thisTid, const QString &package_id, const QString &licence, const QString &group,
					const QString &detail, const QString &url, qulonglong size, const QString &file_list);
private:
	// DBus proxy object to the packagekit daemon
	QPackageKitInterface *iface;

	// Utility functions

	//! Prints the latest DBus error
	void printErrorMessage();

	// Connection variables

	//! Holds the transaction id
	QMap<QString, QString> tids;

	// Transaction management

	//! Allocates a transaction id
	QString allocateTid(QString type);

};

#endif
