/*
* Copyright (C) 2007 Adrien Bustany <madcat@mymadcat.com>
*
* Licensed under the GNU General Public License Version 2
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 See MA 02111-1307, USA.
*
*/

#ifndef DAEMON_H
#define DAEMON_H

#include <QtCore>

#include "CentralProxy.h"

#include "Transaction.h"
#include "Role.h"

namespace PackageKit {

class PolkitClient;

class Daemon : public QObject {

	friend class Transaction;

	Q_OBJECT

public:
	Daemon(QObject *parent = 0);
	~Daemon();

	// PackageKit functions
	QStringList getActions();
	void getBackendDetails(QString &name, QString &author);
	QStringList getFilters();
	QStringList getGroups();
	QStringList getTransactionList();

	uint getTimeSinceAction(Role::Value role);

	bool getNetworkState();
	void setProxy(const QString &http_proxy, const QString &ftp_proxy);
	void suggestQuit();
	void stateHasChanged(const QString &reason);

	Transaction* newTransaction();

protected:
	QString getTid();

private:
	CentralProxy *proxy;
	PolkitClient *polkit;

private slots:
	void NetworkStateChanged_cb(const QString &status);

signals:
	void NetworkStateChanged(bool status);
	void Locked(bool locked);
	void TransactionListChanged(const QStringList &tids);
	void RepoListChanged();
	void RestartSchedule();

};

} // End namespace PackageKit

#endif
