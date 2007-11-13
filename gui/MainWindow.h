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

	// Remove button clicked
	void removePackage();

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

	// Describe the current operation
	typedef enum {
		IDLE,
		SEARCH,
		DESCRIPTION,
		INSTALL,
		REMOVE
	} CurrentOperation;
	CurrentOperation currentOperation;

	// Last search and filters, used to reload the view after an install
	QString lastSearch;
	QList<QPackageKitClient::Filter::FilterEnum> lastFilters;
};
