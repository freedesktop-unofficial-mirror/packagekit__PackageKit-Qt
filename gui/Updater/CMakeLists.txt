set(kpk_update_SRCS
    kpk-update.cpp
    PkUpdate.cpp
    PkAddRm_Model.cpp
    PkAddRm_Delegate.cpp
    pkg_item.cpp
    ../Common/PkTransaction.cpp
    ../Common/PkStrings.cpp
)
kde4_add_ui_files(kpk_update_SRCS
    PkUpdate.ui
    ../Common/PkTransaction.ui
)

kde4_add_plugin(kcm_kpk_update ${kpk_update_SRCS})
target_link_libraries(kcm_kpk_update ${KDE4_KDEUI_LIBS} ${QPACKAGEKIT_LIB})

install(TARGETS kcm_kpk_update DESTINATION ${PLUGIN_INSTALL_DIR} )
