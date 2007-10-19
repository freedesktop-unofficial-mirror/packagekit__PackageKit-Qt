#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	setupUi(this);

	// Set up communication with PackageKit
	pkController = new QPackageKitClient(this);

	// Connect the "Find" button
	connect(buttonFind, SIGNAL(clicked()), this, SLOT(doSearch()));

	// Handle the packages sent by the controller
	connect(pkController, SIGNAL(Package(const QString&, const QString&, const QString&)), this,
					SLOT(newPackage(const QString&, const QString&, const QString&)));

	// Notice when a transaction finishes
	connect(pkController, SIGNAL(Finished(QPackageKitClient::Exit::ExitEnum, uint)), this,
				SLOT(transactionFinished(QPackageKitClient::Exit::ExitEnum, uint)));

	// Hide the details since we don't need them yet
	descriptionTabs->hide();
}

void MainWindow::doSearch() {
	QList<QPackageKitClient::Filter::FilterEnum> filters;

	switch (comboInstalled->currentIndex()) {
		case 1: filters.append(QPackageKitClient::Filter::Installed); break;
		case 2: filters.append(QPackageKitClient::Filter::Available); break;
		default: break;
	}

	switch (comboDevelopment->currentIndex()) {
		case 1: filters.append(QPackageKitClient::Filter::Development); break;
		case 2: filters.append(QPackageKitClient::Filter::Normal); break;
		default: break;
	}

	switch (comboGraphical->currentIndex()) {
		case 1: filters.append(QPackageKitClient::Filter::Gui); break;
		case 2: filters.append(QPackageKitClient::Filter::Text); break;
		default: break;
	}

	buttonFind->setEnabled(false);

	pkController->searchName(searchField->text(), filters);
}

void MainWindow::newPackage(const QString &info, const QString &package_id, const QString &summary) {
	qDebug() << "Got package " << package_id;
}

void MainWindow::transactionFinished(QPackageKitClient::Exit::ExitEnum exitCode, uint runtime) {
	buttonFind->setEnabled(true);
	statusbar->showMessage(QString("Transaction finished in %1 seconds").arg(runtime));
}
