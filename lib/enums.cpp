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

#include "QPackageKitClient.h"

QMap<int, QString> QPackageKitClient::Role::stringValues = QMap<int, QString>();
void QPackageKitClient::Role::construct () {
	stringValues[Cancel] = "cancel";
	stringValues[Resolve] = "resolve";
	stringValues[Rollback] = "rollback";
	stringValues[Get_depends] = "get-depends";
	stringValues[Get_update_detail] = "get-update-detail";
	stringValues[Get_description] = "get-description";
	stringValues[Get_requires] = "get-requires";
	stringValues[Get_updates] = "get-updates";
	stringValues[Search_details] = "search-details";
	stringValues[Search_file] = "search-file";
	stringValues[Search_group] = "search-group";
	stringValues[Search_name] = "search-name";
	stringValues[Refresh_cache] = "refresh-cache";
	stringValues[Update_system] = "update-system";
	stringValues[Remove_package] = "remove-package";
	stringValues[Install_package] = "install-package";
	stringValues[Install_file] = "install-file";
	stringValues[Update_package] = "update-package";
	stringValues[Get_repo_list] = "get-repo-list";
	stringValues[Repo_enable] = "repo-enable";
	stringValues[Repo_set_data] = "repo-set-data";
	stringValues[Unknown] = "unknown";
}

QString QPackageKitClient::Role::toString(RoleEnum e) {
	if(stringValues.size() == 0) construct();
	return stringValues[e];
}

QPackageKitClient::Role::RoleEnum QPackageKitClient::Role::fromString(QString s) {
	if(stringValues.size() == 0) construct();
	return (RoleEnum)stringValues.key(s);
}

QMap<int, QString> QPackageKitClient::Status::stringValues = QMap<int, QString>();
void QPackageKitClient::Status::construct () {
	//Status enum
	stringValues[Setup] = "setup";
	stringValues[Wait] = "wait";
	stringValues[Query] = "query";
	stringValues[Remove] = "remove";
	stringValues[Refresh_cache] = "refresh-cache";
	stringValues[Download] = "download";
	stringValues[Install] = "install";
	stringValues[Update] = "update";
	stringValues[Unknown] = "unknown";
}

QString QPackageKitClient::Status::toString(StatusEnum e) {
	if(stringValues.size() == 0) construct();
	return stringValues[e];
}

QPackageKitClient::Status::StatusEnum QPackageKitClient::Status::fromString(QString s) {
	if(stringValues.size() == 0) construct();
	return (StatusEnum)stringValues.key(s);
}

QMap<int, QString> QPackageKitClient::Exit::stringValues = QMap<int, QString>();
void QPackageKitClient::Exit::construct () {
	stringValues[Success] = "success";
	stringValues[Failed] = "failed";
	stringValues[Canceled] = "canceled";
	stringValues[Unknown] = "unknown";
}

QString QPackageKitClient::Exit::toString(ExitEnum e) {
	if(stringValues.size() == 0) construct();
	return stringValues[e];
}

QPackageKitClient::Exit::ExitEnum QPackageKitClient::Exit::fromString(QString s) {
	if(stringValues.size() == 0) construct();
	return (ExitEnum)stringValues.key(s);
}

QMap<int, QString> QPackageKitClient::Filter::stringValues = QMap<int, QString>();
void QPackageKitClient::Filter::construct () {
	stringValues[Development] = "development";
	stringValues[Installed] = "installed";
	stringValues[Gui] = "gui";
	stringValues[Normal] = "~devel";
	stringValues[Available] = "~installed";
	stringValues[Text] = "~gui";
	stringValues[Unknown] = "unknown";
}

QString QPackageKitClient::Filter::toString(FilterEnum e) {
	if(stringValues.size() == 0) construct();
	return QPackageKitClient::Filter::stringValues[e];
}

QPackageKitClient::Filter::FilterEnum QPackageKitClient::Filter::fromString(QString s) {
	if(stringValues.size() == 0) construct();
	return (FilterEnum)stringValues.key(s);
}

