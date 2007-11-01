#include <QtGui>

#include "ui_mainwindow.h"
#include <QPackageKitClient.h>

class QPackageKitClient;
class PackageModel;

class MainWindow : public QMainWindow, private Ui::MainWindow {

	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

public slots:
	// "Find" button clicked
	void doSearch();

	// Install button clicked
	void installPackage();

	// The controller sent us a package
	void newPackage(const QString& info, const QString& package_id, const QString& summary);

	// A transaction finished
	void transactionFinished(QPackageKitClient::Exit::ExitEnum exitCode, uint runtime);

	// We got some package's description
	void gotDescription(const QString &package_id, const QString &licence, const QString &group,
			const QString &detail, const QString &url, qulonglong size, const QString &file_list);

	// Make the progress bar in the status bar spin
	void spinProgressBar();

	// Update the progress info
	void updateProgress(uint percentage, uint subpercentage, uint elapsed, uint remaining);

	// Resets the progress bar status (progress 100%);
	void resetProgressBar();

	// Fetch the description/files/etc of a package
	void updatePackageDetails(const QModelIndex &index);

private:
	// Controls the package kit client
	QPackageKitClient *pkController;

	// Stores the list of packages to display
	PackageModel *packageModel;

	// The progress bar in the status bar
	QProgressBar *progressBar;

	// Ctrl Q, quit the application
	QShortcut *quitShortcut;

	// Pointer to the currently selected package
	QString currentPackageId;

};
