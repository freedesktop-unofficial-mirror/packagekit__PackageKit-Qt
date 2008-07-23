/***************************************************************************
 *   Copyright (C) 2008 by Daniel Nicoletti   *
 *   dantti85-pk@yahoo.com.br   *
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

#include <KDebug>

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

QString PkStrings::Error(Error::Value v)
{
    switch (v) {
	case Error::Oom :
	    return i18n("Out of memory");
	case Error::No_network :
	    return i18n("No network connection available");
	case Error::Not_supported :
	    return i18n("Not supported by this backend");
	case Error::Internal_error :
	    return i18n("An internal system error has occurred");
	case Error::Gpg_failure :
	    return i18n("A security trust relationship is not present");
	case Error::Package_id_invalid :
	    return i18n("The package identifier was not well formed");
	case Error::Package_not_installed :
	    return i18n("The package is not installed");
	case Error::Package_not_found :
	    return i18n("The package was not found");
	case Error::Package_already_installed :
	    return i18n("The package is already installed");
	case Error::Package_download_failed :
	    return i18n("The package download failed");
	case Error::Group_not_found :
	    return i18n("The group was not found");
	case Error::Group_list_invalid :
	    return i18n("The group list was invalid");
	case Error::Dep_resolution_failed :
	    return i18n("Dependency resolution failed");
	case Error::Filter_invalid :
	    return i18n("Search filter was invalid");
	case Error::Create_thread_failed :
	    return i18n("Failed to create a thread");
	case Error::Transaction_error :
	    return i18n("Transaction error");
	case Error::Transaction_cancelled :
	    return i18n("The task was canceled");
	case Error::No_cache :
	    return i18n("No package cache is available");
	case Error::Repo_not_found :
	    return i18n("Repository name was not found");
	case Error::Cannot_remove_system_package :
	    return i18n("Could not remove a protected system package");
	case Error::Process_kill :
	    return i18n("The task was forcibly canceled");
	case Error::Failed_initialization :
	    return i18n("Failed to initialize");
	case Error::Failed_finalise :
	    return i18n("Failed to finalise");
	case Error::Failed_config_parsing :
	    return i18n("Reading the config file failed");
	case Error::Cannot_cancel :
	    return i18n("The task cannot be cancelled");
	case Error::Cannot_getLock :
	    return i18n("Cannot get lock");
	case Error::No_packages_to_update :
	    return i18n("No packages to update");
	case Error::Cannot_write_repo_config :
	    return i18n("Cannot write repository configuration");
	case Error::Local_install_failed :
	    return i18n("Local install failed");
	case Error::Bad_gpg_signature :
	    return i18n("Bad GPG signature");
	case Error::Missing_gpg_signature :
	    return i18n("Missing GPG signature");
	case Error::Cannot_install_source_package :
	    return i18n("Source packages cannot be installed");
	case Error::Repo_configuration_error :
	    return i18n("Repository configuration invalid");
	case Error::No_license_agreement :
	    return i18n("The license agreement failed");
	case Error::File_conflicts :
	    return i18n("Local file conflict between packages");
	case Error::Repo_not_available :
	    return i18n("Problem connecting to a software source");
	case Error::Invalid_package_file :
	    return i18n("Invalid package file");
	case Error::Package_install_blocked :
	    return i18n("Package install blocked");
	case Error::Package_corrupt :
	    return i18n("Package is corrupt");
	case Error::Unknown :
	    return i18n("Unknown error");
	default :
	    return i18n("Unknown error");
    }
}

QString PkStrings::ErrorMessage(Error::Value v)
{
    switch (v) {
	case Error::Oom :
	    return i18n("The service that is responsible for handling user requests is out of memory.\n"
			"Please restart your computer.");
	case Error::No_network :
	    return i18n("There is no network connection available.\n"
			"Please check your connection settings and try again");
	case Error::Not_supported :
	    return i18n("The action is not supported by this backend.\n"
			"Please report a bug as this shouldn't have happened.");
	case Error::Internal_error :
	    return i18n("A problem that we were not expecting has occurred.\n"
			"Please report this bug with the error description.");
	case Error::Gpg_failure :
	    return i18n("A security trust relationship could not be made with software source.\n"
			"Please check your security settings.");
	case Error::Package_id_invalid :
	    return i18n("The package identifier was not well formed when sent to the server.\n"
			"This normally indicates an internal error and should be reported.");
	case Error::Package_not_installed :
	    return i18n("The package that is trying to be removed or updated is not already installed.");
	case Error::Package_not_found :
	    return i18n("The package that is being modified was not found on your system or in any software source.");
	case Error::Package_already_installed :
	    return i18n("The package that is trying to be installed is already installed.");
	case Error::Package_download_failed :
	    return i18n("The package download failed.\n"
			"Please check your network connectivity.");
	case Error::Group_not_found :
	    return i18n("The group type was not found.\n"
			"Please check your group list and try again.");
	case Error::Group_list_invalid :
	    return i18n("The group list could not be loaded.\n"
			"Refreshing your cache may help, although this is normally a software "
			"source error.");
	case Error::Dep_resolution_failed :
	    return i18n("A package could not be found that allows the task to complete.\n"
			"More information is available in the detailed report.");
	case Error::Filter_invalid :
	    return i18n("The search filter was not correctly formed.");
	case Error::Create_thread_failed :
	    return i18n("A thread could not be created to service the user request.");
	case Error::Transaction_error :
	    return i18n("An unspecified task error has occurred.\n"
			"More information is available in the detailed report.");
	case Error::Transaction_cancelled :
	    return i18n("The task was canceled successfully and no packages were changed.");
	case Error::No_cache :
	    return i18n("The package list needs to be rebuilt.\n"
			"This should have been done by the backend automatically.");
	case Error::Repo_not_found :
	    return i18n("The remote software source name was not found.\n"
			"You may need to enable an item in Software Sources.");
	case Error::Cannot_remove_system_package :
	    return i18n("Removing a protected system package is not alloed.");
	case Error::Process_kill :
	    return i18n("The task was canceled successfully and no packages were changed.\n"
			"The backend did not exit cleanly.");
	case Error::Failed_initialization :
	    return i18n("Failed to initialize packaging backend.\n"
			"This may occur if other packaging tools are being used simultaneously.");
	case Error::Failed_finalise :
	    return i18n("Failed to close down the backend instance.\n"
			"This error can normally be ignored.");
	case Error::Failed_config_parsing :
	    return i18n("The native package configuration file could not be opened.\n"
			"Please make sure configuration is valid.");
	case Error::Cannot_cancel :
	    return i18n("The task is not safe to be cancelled at this time.");
	case Error::Cannot_getLock :
	    return i18n("Cannot get the exclusive lock on the packaging backend.\n"
			"Please close any other legacy packaging tools that may be open.");
	case Error::No_packages_to_update :
	    return i18n("None of the selected packages could be updated.");
	case Error::Cannot_write_repo_config :
	    return i18n("The repository configuration could not be modified.");
	case Error::Local_install_failed :
	    return i18n("Installing the local file failed.\n"
			"More information is available in the detailed report.");
	case Error::Bad_gpg_signature :
	    return i18n("The package signature could not be verified.");
	case Error::Missing_gpg_signature :
	    return i18n("The package signature was missing and this package is untrusted.\n"
			"This package was not signed with a GPG key when created.");
	case Error::Cannot_install_source_package :
	    return i18n("Source packages are not normally installed this way.\n"
			"Check the extension of the file you are trying to install.");
	case Error::Repo_configuration_error :
	    return i18n("Repository configuration was invalid and could not be read.");
	case Error::No_license_agreement :
	    return i18n("The license agreement was not agreed to.\n"
			"To use this software you have to accept the license.");
	case Error::File_conflicts :
	    return i18n("Two packages provide the same file.\n"
			"This is usually due to mixing packages for different software sources.");
	case Error::Repo_not_available :
	    return i18n("There was a (possibly temporary) problem connecting to a software source\n"
			"Please check the detailed error for further details.");
	case Error::Invalid_package_file :
	    return i18n("The package you are attempting to install is not valid.\n"
			"The package file could be corrupt, or not a proper package.");
	case Error::Package_install_blocked :
	    return i18n("Installation of this package prevented by your packaging system's configuration.");
	case Error::Package_corrupt :
	    return i18n("The package that was downloaded is corrupt and needs to be downloaded again.");
	case Error::Unknown :
	    return i18n("Unknown error, please report a bug.\n"
			"More information is available in the detailed report.");
	default :
	    return i18n("Unknown error, please report a bug.\n"
			"More information is available in the detailed report.");
    }
}

QString PkStrings::Groups(Groups::Value v)
{
    switch (v) {
        case Groups::Accessibility :
	    return i18n("Accessibility");
        case Groups::Accessories :
	    return i18n("Accessories");
        case Groups::Admin_tools :
	    return i18n("Admin tools");
        case Groups::Communication :
	    return i18n("Communication");
        case Groups::Desktop_gnome :
	    return i18n("GNOME desktop");
        case Groups::Desktop_kde :
	    return i18n("KDE desktop");
        case Groups::Desktop_other :
	    return i18n("Other desktops");
        case Groups::Desktop_xfce :
	    return i18n("XFCE desktop");
        case Groups::Education :
	    return i18n("Education");
        case Groups::Fonts :
	    return i18n("Fonts");
        case Groups::Games :
	    return i18n("Games");
        case Groups::Graphics :
	    return i18n("Graphics");
        case Groups::Internet :
	    return i18n("Internet");
        case Groups::Legacy :
	    return i18n("Legacy");
        case Groups::Localization :
	    return i18n("Localization");
        case Groups::Maps :
	    return i18n("Maps");
        case Groups::Multimedia :
	    return i18n("Multimedia");
        case Groups::Network :
	    return i18n("Network");
        case Groups::Office :
	    return i18n("Office");
        case Groups::Other :
	    return i18n("Other");
        case Groups::Power_management :
	    return i18n("Power management");
        case Groups::Programming :
	    return i18n("Development");
        case Groups::Publishing :
	    return i18n("Publishing");
        case Groups::Repos :
	    return i18n("Software sources");
        case Groups::Security :
	    return i18n("Security");
        case Groups::Servers :
	    return i18n("Servers");
        case Groups::System :
	    return i18n("System");
        case Groups::Virtualization :
	    return i18n("Virtualization");
        case Groups::Unknown :
	    return i18n("Unknown group");
        default :
	    return i18n( "group unrecognised" );
    }
}

KIcon PkStrings::GroupsIcon(Groups::Value v)
{
    switch (v) {
        case Groups::Accessibility :
	    return KIcon("preferences-desktop-accessibility");
        case Groups::Accessories :
	    return KIcon("applications-accessories");
        case Groups::Admin_tools :
	    return KIcon("dialog-password");
        case Groups::Communication :
	    return KIcon("network-workgroup");//FIXME
        case Groups::Desktop_gnome :
	    return KIcon("user-desktop");//FIXME
        case Groups::Desktop_kde :
	    return KIcon("kde");
        case Groups::Desktop_other :
	    return KIcon("user-desktop");
        case Groups::Desktop_xfce :
	    return KIcon("user-desktop");//FIXME
        case Groups::Education :
	    return KIcon("applications-education");
        case Groups::Fonts :
	    return KIcon("preferences-desktop-font");
        case Groups::Games :
	    return KIcon("applications-games");
        case Groups::Graphics :
	    return KIcon("applications-graphics");
        case Groups::Internet :
	    return KIcon("applications-internet");
        case Groups::Legacy :
	    return KIcon("media-floppy");
        case Groups::Localization :
	    return KIcon("applications-education-language");
        case Groups::Maps :
	    return KIcon("Maps");//FIXME
        case Groups::Multimedia :
	    return KIcon("applications-multimedia");
        case Groups::Network :
	    return KIcon("network-wired");
        case Groups::Office :
	    return KIcon("applications-office");
        case Groups::Other :
	    return KIcon("applications-other");
        case Groups::Power_management :
	    return KIcon("battery");
        case Groups::Programming :
	    return KIcon("applications-development");
        case Groups::Publishing :
	    return KIcon("accessories-text-editor");
        case Groups::Repos :
	    return KIcon("application-x-compressed-tar");
        case Groups::Security :
	    return KIcon("security-high");
        case Groups::Servers :
	    return KIcon("network-server");
        case Groups::System :
	    return KIcon("applications-system");
        case Groups::Virtualization :
	    return KIcon("cpu");
        case Groups::Unknown :
	    return KIcon("unknown");
        default :
	    return KIcon("unknown");
    }
}

QString PkStrings::Info(Info::Value v)
{
    switch (v) {
        case Info::Low :
	    return i18n("Trivial update");
        case Info::Normal :
	    return i18n("Update");
        case Info::Important :
	    return i18n("Important update");
        case Info::Security :
	    return i18n("Security update");
        case Info::Bugfix :
	    return i18n("Bug fix update");
        case Info::Enhancement :
	    return i18n("Enhancement update");
        case Info::Blocked :
	    return i18n("Blocked update");
        case Info::Installed :
	    return i18n("Installed");
        case Info::Available :
	    return i18n("Available");
        case Info::Unknown :
	    return i18n("Unknown update");
        default :
	    kDebug() << "info unrecognised: " << v;
	    return QString();
    }
}

QString PkStrings::InfoUpdate(Info::Value v, int number)
{
    switch (v) {
        case Info::Low :
	    return i18np("1 trivial update", "%1 trivial updates", number);
        case Info::Normal :
	    return i18np("1 update", "%1 updates", number);
        case Info::Important :
	    return i18np("1 important update", "%1 important updates", number);
        case Info::Security :
	    return i18np("1 security update", "%1 security updates", number);
        case Info::Bugfix :
	    return i18np("1 bug fix update", "%1 bug fix updates", number);
        case Info::Enhancement :
	    return i18np("1 enhancement update", "%1 enhancement updates", number);
        default :
	    kDebug() << "update info unrecognised: " << v;
	    return i18np("1 unknown update", "%1 unknown updates", number);
    }
}

#include "PkStrings.moc"
