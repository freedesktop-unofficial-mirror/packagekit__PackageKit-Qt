#ifndef QPACKAGEKITCLIENT_H
#define QPACKAGEKITCLIENT_H

#include <QtCore>
#include <QtDBus>

#include "QPackageKitInterface.h"

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

	private:
		static QMap<int, QString> stringValues;
	};
	// End Enums

	//! QPackageKitClient constructor
	QPackageKitClient(QObject *parent = 0);

	//! Searches for a package using its name
	bool searchName(QString name, QList<Filter::FilterEnum> filters);

signals:
	 void Package(const QString &info, const QString &package_id, const QString &summary);
	 void Finished(QPackageKitClient::Exit::ExitEnum exitCode, uint runtime);
	
public slots:
	void newPackage(const QString &thisTid, const QString &info, const QString &package_id, const QString &summary);
	void transactionFinished(const QString &thisTid, const QString &status, uint runtime);
private:
	QPackageKitInterface *iface;

	// Utility functions

	//! Prints the latest DBus error
	void printErrorMessage();

	// Connection variables

	//! Holds the transaction id
	QString tid;

	// Transaction management

	//! Allocates a transaction id
	bool allocateTid();

};

#endif
