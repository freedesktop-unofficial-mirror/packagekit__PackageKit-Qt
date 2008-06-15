/***************************************************************************
 *   Copyright (C) 2008 by Daniel Nicoletti   *
 *   mirttex85-pk@yahoo.com.br   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <KLocale>

#include <KMessageBox>

#include "PkStrings.h"

PkStrings::PkStrings( QObject *parent )
 : QObject(parent)
{
}

PkStrings::~PkStrings()
{
}

QString PkStrings::StatusChanged(Status::Value v)
{
    switch (v) {
        case Status::Setup :
	    return i18n("Waiting for service to start");
        case Status::Wait :
	    return i18n("Waiting for other tasks");
        case Status::Query :
	    return i18n("Querying");
        case Status::Info :
	    return i18n("Getting information");
        case Status::Remove :
	    return i18n("Removing");
        case Status::Refresh_cache :
	    return i18n("Refreshing software list");
        case Status::Download :
	    return i18n("Downloading");
        case Status::Install :
	    return i18n("Installing");
        case Status::Update :
	    return i18n("Updating");
        case Status::Cleanup :
	    return i18n("Cleaning Up");
        case Status::Obsolete :
	    return i18n("Obsoletiong");
        case Status::Dep_resolve :
	    return i18n("Resolving dependencies");
        case Status::Rollback :
	    return i18n("Rolling back");
        case Status::Commit :
	    return i18n("Committing changes");
        case Status::Request :
	    return i18n("Requesting data");
        case Status::Finished :
	    return i18n("Finished");
        case Status::Cancel :
	    return i18n("Cancelling");
        case Status::Unknown :
	    return i18n("Unknown state");
	default :
	    return i18n("Running task");
    }
}

QString PkStrings::ErrorCode(Error::Value v)
{
    switch (v) {
	case Error::Oom :
	    return i18n("Waiting for service to start");
	case Error::No_network :
	    return i18n("Waiting for service to start");
	case Error::Not_supported :
	    return i18n("Waiting for service to start");
	case Error::Internal_error :
	    return i18n("Waiting for service to start");
	case Error::Gpg_failure :
	    return i18n("Waiting for service to start");
	case Error::Package_id_invalid :
	    return i18n("Waiting for service to start");
	case Error::Package_not_installed :
	    return i18n("Waiting for service to start");
	case Error::Package_not_found :
	    return i18n("Waiting for service to start");
	case Error::Package_already_installed :
	    return i18n("Waiting for service to start");
	case Error::Package_download_failed :
	    return i18n("Waiting for service to start");
	case Error::Group_not_found :
	    return i18n("Waiting for service to start");
	case Error::Group_list_invalid :
	    return i18n("Waiting for service to start");
	case Error::Dep_resolution_failed :
	    return i18n("Waiting for service to start");
	case Error::Filter_invalid :
	    return i18n("Waiting for service to start");
	case Error::Create_thread_failed :
	    return i18n("Waiting for service to start");
	case Error::Transaction_error :
	    return i18n("Waiting for service to start");
	case Error::Transaction_cancelled :
	    return i18n("Waiting for service to start");
	case Error::No_cache :
	    return i18n("Waiting for service to start");
	case Error::Repo_not_found :
	    return i18n("Waiting for service to start");
	case Error::Cannot_remove_system_package :
	    return i18n("Waiting for service to start");
	case Error::Process_kill :
	    return i18n("Waiting for service to start");
	case Error::Failed_initialization :
	    return i18n("Waiting for service to start");
	case Error::Failed_finalise :
	    return i18n("Waiting for service to start");
	case Error::Failed_config_parsing :
	    return i18n("Waiting for service to start");
	case Error::Cannot_cancel :
	    return i18n("Waiting for service to start");
	case Error::Cannot_getLock :
	    return i18n("Waiting for service to start");
	case Error::No_packages_to_update :
	    return i18n("Waiting for service to start");
	case Error::Cannot_write_repo_config :
	    return i18n("Waiting for service to start");
	case Error::Local_install_failed :
	    return i18n("Waiting for service to start");
	case Error::Bad_gpg_signature :
	    return i18n("Waiting for service to start");
	case Error::Missing_gpg_signature :
	    return i18n("Waiting for service to start");
	case Error::Cannot_install_source_package :
	    return i18n("Waiting for service to start");
	case Error::Repo_configuration_error :
	    return i18n("Waiting for service to start");
	case Error::No_license_agreement :
	    return i18n("Waiting for service to start");
	case Error::File_conflicts :
	    return i18n("Waiting for service to start");
	case Error::Repo_not_available :
	    return i18n("Waiting for service to start");
	case Error::Invalid_package_file :
	    return i18n("Waiting for service to start");
	case Error::Package_install_blocked :
	    return i18n("Waiting for service to start");
	case Error::Package_corrupt :
	    return i18n("Waiting for service to start");
	case Error::Unknown :
	    return i18n("Waiting for service to start");
	default :
	    return i18n("Unknown Error");
    }
}

// void PkTransaction::ErrorCode(const QString &one, const QString &two)
// {
//     KMessageBox::detailedSorry( this, one, two, i18n("Erro PackageKit"), KMessageBox::Notify );
// }

// void PkTransaction::Finished(Exit::Value status, uint /*runtime*/)
// {
//     qDebug() << "trans finished: " << status ;
//     switch(status) {
//         case Exit::Success :
// 	    qDebug() << "trans succes: ";
// 	    break;
// 	case Exit::Failed :
// 	    qDebug() << "trans failed: ";
//             m_notifyT.start(50);
// 	    break;
// 	case Exit::Kill :
//             qDebug() << "trans quit: ";
//             break;
// 	case Exit::Unknown :
//             qDebug() << "trans quit: ";
//             break;
//     }
// }

#include "PkStrings.moc"
