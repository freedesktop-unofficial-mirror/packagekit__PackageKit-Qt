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

#include "MainWindow.h"

#include "PackageModel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	setupUi(this);

	// Set up communication with PackageKit
	pkController = new QPackageKitClient(this);

	// Set up the model
	packageModel = new PackageModel(this);
	packageListView->setModel(packageModel);

	// Add the progress bar in the status bar
	progressBar = new QProgressBar(this);
	progressBar->setValue(progressBar->maximum());
	statusbar->addPermanentWidget(progressBar);

	// Instantiate and connect the quit shortcut
	quitShortcut = new QShortcut(QKeySequence(tr("Ctrl+Q")), this);
	connect(quitShortcut, SIGNAL(activated()), this, SLOT(close()));

	// Connect the "Find" button
	connect(buttonFind, SIGNAL(clicked()), this, SLOT(doSearch()));
	connect(comboInstalled, SIGNAL(currentIndexChanged(int)), this, SLOT(doSearch()));
	connect(comboDevelopment, SIGNAL(currentIndexChanged(int)), this, SLOT(doSearch()));
	connect(comboGraphical, SIGNAL(currentIndexChanged(int)), this, SLOT(doSearch()));

	// Connect the "Install" button
	connect(buttonInstall, SIGNAL(clicked()), this, SLOT(installPackage()));

	// Connect the "Remove" button
	connect(buttonRemove, SIGNAL(clicked()), this, SLOT(removePackage()));

	// Handle the packages sent by the controller
	connect(pkController, SIGNAL(Package(const QString&, const QString&, const QString&)), this,
					SLOT(newPackage(const QString&, const QString&, const QString&)));

	// Notice when a transaction finishes
	connect(pkController, SIGNAL(Finished(QPackageKitClient::Exit::ExitEnum, uint)), this,
				SLOT(transactionFinished(QPackageKitClient::Exit::ExitEnum, uint)));

	// Be warned when there will be no percentage updates
	connect(pkController, SIGNAL(NoProgressUpdates()), this, SLOT(spinProgressBar()));

	// And update the progress bar when there are some
	connect(pkController, SIGNAL(ProgressChanged(uint, uint, uint, uint)), this, SLOT(updateProgress(uint, uint, uint, uint)));

	// Update the details pane when asked
	connect(pkController, SIGNAL(Description(const QString&, const QString&, const QString&, const QString&, const QString&,
		qulonglong, const QString&)), this, SLOT(gotDescription(const QString&, const QString&, const QString&, const QString&,
												const QString&, qulonglong, const QString&)));

	// Be notified when the current item changes in the package list
	connect(packageListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
							this, SLOT(updatePackageDetails(const QModelIndex&)));

	// Hide the details since we don't need them yet
	descriptionTabs->hide();

	// Wer're doing nothing
	currentOperation = IDLE;
}

void MainWindow::doSearch() {

	// Construct the search filter
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

	// Put the interface in a waiting state
	packageModel->clear();
	buttonFind->setEnabled(false);
	setCursor(Qt::WaitCursor);
	currentOperation = SEARCH;

	// Save the search to be able to reload the view
	lastSearch = searchField->text();
	lastFilters = filters;

	// Launch the actual search
	pkController->searchName(searchField->text(), filters);
}

void MainWindow::installPackage() {
	currentOperation = INSTALL;
	PkPackage *p = packageModel->packageAtIndex(packageListView->currentIndex());
	pkController->installPackage(p);
}

void MainWindow::removePackage() {
	currentOperation = REMOVE;
	PkPackage *p = packageModel->packageAtIndex(packageListView->currentIndex());
	pkController->removePackage(p);
}


void MainWindow::newPackage(const QString &info, const QString &package_id, const QString &summary) {
	if(currentOperation != SEARCH) return;
	packageModel->addPackage(package_id, info == "installed" ? true : false);
	packageModel->sort();
}

void MainWindow::transactionFinished(QPackageKitClient::Exit::ExitEnum exitCode, uint runtime) {
	currentOperation = IDLE;
	setCursor(Qt::ArrowCursor);
	buttonFind->setEnabled(true);
	statusbar->showMessage(QString("Transaction finished in %1 seconds with status %2").arg(runtime/1000).arg(QPackageKitClient::Exit::toString(exitCode)));
	resetProgressBar();
}

void MainWindow::spinProgressBar() {
	progressBar->setTextVisible(false);
	progressBar->setMinimum(0);
	progressBar->setMaximum(0);
}

void MainWindow::resetProgressBar() {
	progressBar->setTextVisible(true);
	progressBar->setMaximum(100);
	progressBar->setValue(progressBar->maximum());
}

void MainWindow::updatePackageDetails(const QModelIndex& index) {
	descriptionTabs->show();
	descriptionTabs->setEnabled(false);
	PkPackage *p = packageModel->packageAtIndex(index);
	// !p happens when the model gets cleared, because the view changes current
	if(!p || p == (PkPackage*)0x1) return;
	currentOperation = DESCRIPTION;
	currentPackageId = p->id();
	pkController->getDescription(p);
}

void MainWindow::updateProgress(uint percentage, uint subpercentage, uint elapsed, uint remaining) {
	progressBar->setValue(percentage);
}

void MainWindow::gotDescription(const QString &package_id, const QString &licence, const QString &group,
			const QString &detail, const QString &url, qulonglong size, const QString &file_list) {
	qDebug() << "Got a description for package " << package_id;
	// If the description is not for the selected package, then we don't want it
	if(currentPackageId != package_id) return;
	if(currentOperation != DESCRIPTION) return;

	detail_licence->setText(licence);
	detail_group->setText(group);
	detail_desc->setText(detail);
	detail_url->setText(QString("<a href=\"%1\">%1</a>").arg(url));
	detail_size->setText(QString("%1 kb").arg(size));
	QStringListModel *filesModel = new QStringListModel(file_list.split(";"), this);
	detail_files->setModel(filesModel);

	descriptionTabs->setEnabled(true);
}
