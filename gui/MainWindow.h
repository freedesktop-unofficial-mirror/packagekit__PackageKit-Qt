#include <QtGui>

#include "ui_mainwindow.h"
#include "../lib/QPackageKitClient.h"

class QPackageKitClient;

class MainWindow : public QMainWindow, private Ui::MainWindow {

	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

public slots:
	// "Find" button clicked
	void doSearch();

	// The controller sent us a package
	void newPackage(const QString& info, const QString& package_id, const QString& summary);

	// A transaction finished
	void transactionFinished(QPackageKitClient::Exit::ExitEnum exitCode, uint runtime);

private:
	QPackageKitClient *pkController;

};
