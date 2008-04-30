project(KPackageKit)
find_package(KDE4 REQUIRED)

add_subdirectory(desktop)

include(KDE4Defaults)
link_directories( /home/daniel/projetos/PackageKit/QPackageKit/lib/ )
# ${CMAKE_BINARY_DIR}
add_definitions(${QT_DEFINITIONS} ${KDE_DEFINITIONS})
include_directories( ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES} ${KDE4_KIO_INCLUDES} )

############ PK ADD RM #######################
set(kpk_addrm_SRCS
    kpk-addrm.cpp
    AddRm/PkAddRm.cpp
    AddRm/PkAddRm_Model.cpp
    AddRm/PkAddRm_Delegate.cpp
)

kde4_add_ui_files(kpk_addrm_SRCS
    AddRm/PkAddRm.ui
)

kde4_add_plugin(kcm_kpk_addrm ${kpk_addrm_SRCS})
target_link_libraries(kcm_kpk_addrm ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} ${KDE4_KNEWSTUFF2_LIBS} packagekit-qt )

install(TARGETS kcm_kpk_addrm  DESTINATION ${PLUGIN_INSTALL_DIR} )

############ PK Settings #######################

set(kpk_settings_SRCS
    kpk-settings.cpp
    PkSettings.cpp
)
kde4_add_ui_files(kpk_settings_SRCS
    PkSettings.ui
)

kde4_add_plugin(kcm_kpk_settings ${kpk_settings_SRCS})
target_link_libraries(kcm_kpk_settings ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} ${KDE4_KNEWSTUFF2_LIBS})

install(TARGETS kcm_kpk_settings  DESTINATION ${PLUGIN_INSTALL_DIR} )

############ PK UPDATE #######################

set(kpk_update_SRCS
    kpk-update.cpp
    PkUpdate.cpp
)
kde4_add_ui_files(kpk_update_SRCS
    PkUpdate.ui
)

kde4_add_plugin(kcm_kpk_update ${kpk_update_SRCS})
target_link_libraries(kcm_kpk_update ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} ${KDE4_KNEWSTUFF2_LIBS})

install(TARGETS kcm_kpk_update  DESTINATION ${PLUGIN_INSTALL_DIR} )
