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

#include "Daemon.h"
#include "constants.h"
#include "PolkitClient.h"
#include "Actions.h"
#include "Groups.h"

using namespace PackageKit;

Daemon::Daemon(QObject *parent) : QObject(parent) {
	proxy = new CentralProxy(PK_NAME, PK_PATH, QDBusConnection::systemBus(), this);
	connect(proxy, SIGNAL(NetworkStateChanged(const QString&)), this, SLOT(NetworkStateChanged_cb(const QString&)));
	connect(proxy, SIGNAL(Locked(bool)), this, SIGNAL(Locked(bool)));
	connect(proxy, SIGNAL(TransactionListChanged(const QStringList&)), this, SIGNAL(TransactionListChanged(const QStringList&)));
	connect(proxy, SIGNAL(RestartSchedule()), this, SIGNAL(RestartSchedule()));
	connect(proxy, SIGNAL(RepoListChanged()), this, SIGNAL(RepoListChanged()));

	polkit = new PolkitClient(this);
}

Daemon::~Daemon() {
}

unsigned int Daemon::getActions() {
	QStringList actions = QString(proxy->GetActions()).split(";");
	unsigned int ret = 0;
	for(int i = 0 ; i < actions.size() ; ++i) {
		ret |= EnumFromString<Actions>(actions.at(i));
	}
	return ret;
}

void Daemon::getBackendDetails(QString &name, QString &author) {
	name = proxy->GetBackendDetail(author);
}

QStringList Daemon::getFilters() {
	return QString(proxy->GetFilters()).split(";");
}

QStringList Daemon::getGroups() {
	return QString(proxy->GetGroups()).split(";");
}

QStringList Daemon::getTransactionList() {
	return proxy->GetTransactionList();
}

uint Daemon::getTimeSinceAction(Role::Value role) {
	return proxy->GetTimeSinceAction(EnumToString<Role>(role));
}

// 1 = online ; 0 = offline
bool Daemon::getNetworkState() {
	QString state = proxy->GetNetworkState();
   return (state == "online");
}

void Daemon::setProxy(const QString &http_proxy, const QString &ftp_proxy) {
    qDebug() << "Trying to get authorization...";
    if(!polkit->getAuth(AUTH_SETPROXY)) emit AuthRefused("Cannot get authorization to set proxy");;
    qDebug() << "We're authentificated";
	proxy->SetProxy(http_proxy, ftp_proxy);
}

void Daemon::suggestQuit() {
	proxy->SuggestDaemonQuit();
}

void Daemon::stateHasChanged(const QString &reason) {
	proxy->StateHasChanged(reason);
}

Transaction* Daemon::newTransaction() {
	return new Transaction(this);
}

QString Daemon::getTid() {
	return proxy->GetTid();
}

void Daemon::sendAuthRefused(const QString &message) {
	emit AuthRefused(message);
}

void Daemon::NetworkStateChanged_cb(const QString &status) {
	emit NetworkStateChanged((status == "online"));
}

