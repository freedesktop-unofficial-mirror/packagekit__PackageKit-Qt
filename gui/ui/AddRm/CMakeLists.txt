set(kpk_addrm_SRCS
    kpk-addrm.cpp
    PkAddRm.cpp
    PkAddRm_Model.cpp
    PkDelegate.cpp
    PkTransaction.cpp
    PkRequirements.cpp
)

kde4_add_ui_files(kpk_addrm_SRCS
    PkAddRm.ui
    PkTransaction.ui
    PkRequirements.ui
)

kde4_add_plugin(kcm_kpk_addrm ${kpk_addrm_SRCS})
target_link_libraries(kcm_kpk_addrm ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} ${KDE4_KNEWSTUFF2_LIBS} packagekit-qt )

install(TARGETS kcm_kpk_addrm  DESTINATION ${PLUGIN_INSTALL_DIR} )