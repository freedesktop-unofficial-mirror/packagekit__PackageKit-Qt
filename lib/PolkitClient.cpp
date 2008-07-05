#include <polkit-grant/polkit-grant.h>
#include <polkit-dbus/polkit-dbus.h>

#include "PolkitClient.h"
#include "constants.h"

using namespace PackageKit;

PolkitClient::PolkitClient(QObject *parent) : QObject(parent) {
}

bool PolkitClient::getAuth(const QString &action) {
//     DBusError e;
//     dbus_error_init(&e);
    
//     PolKitAction *p_action = polkit_action_new();
    PolKitAction *p_action = polkit_action_new_from_string_representation("org.freedesktop.packagekit.refresh-cache");
    
//     if ( !polkit_action_set_action_id( p_action, "org.freedesktop.packagekit.refresh-cache" ) ) {
//          qDebug() << "polkit action false";
//     }
    qDebug() << "validade" << polkit_action_validate_id("org.freedesktop.packagekit.refresh-cache");
    qDebug() << "check_auth" << polkit_check_auth( QCoreApplication::applicationPid(), "org.freedesktop.packagekit.refresh-cache" );
//         return true;
//     bool auth = polkit_auth_obtain(action.toAscii().data(), 0, QCoreApplication::applicationPid(), &e);
//     if(!auth) {
//         qDebug() << "Authentification error :" << e.name << ":" << e.message;
//     }

    PolKitGrant *p_auth = polkit_grant_new();
    
    
    
    PolKitCaller *p_caller = polkit_caller_new();
    
    if ( !polkit_caller_set_pid( p_caller, QCoreApplication::applicationPid() ) ){
         qDebug() << "polkit caller false";
    }
    
//     polkit_grant_set_functions(p_auth);
    return polkit_grant_initiate_auth(p_auth, p_action, p_caller);
    
//     return auth;
}

