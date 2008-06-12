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

#ifndef ERROR_H
#define ERROR_H

#include <QtCore>

#include "Enum.h"

namespace PackageKit {

class Error : public QObject {

	Q_OBJECT
	Q_ENUMS(Value)

public:
typedef enum {
	Oom,
	NoNetwork,
	NotSupported,
	InternalError,
	GpgFailure,
	PackageIdInvalid,
	PackageNotInstalled,
	PackageNotFound,
	PackageAlreadyInstalled,
	PackageDownloadFailed,
	GroupNotFound,
	GroupListInvalid,
	DepResolutionFailed,
	FilterInvalid,
	CreateThreadFailed,
	TransactionError,
	TransactionCancelled,
	NoCache,
	RepoNotFound,
	CannotRemoveSystemPackage,
	ProcessKill,
	FailedInitialization,
	FailedFinalise,
	FailedConfigParsing,
	CannotCancel,
	CannotGetLock,
	NoPackagesToUpdate,
	CannotWriteRepoConfig,
	LocalInstallFailed,
	BadGpgSignature,
	MissingGpgSignature,
	CannotInstallSourcePackage,
	RepoConfigurationError,
	NoLicenseAgreement,
	FileConflicts,
	RepoNotAvailable,
	InvalidPackageFile,
	PackageInstallBlocked,
	PackageCorrupt,
	Unknown
} Value;

};

} // End namespace PackageKit

#endif
