set(kpk_settings_SRCS
    kpk-settings.cpp
    PkSettings.cpp
    PkConfigSkell.cpp
)
kde4_add_ui_files(kpk_settings_SRCS
    PkSettings.ui
)

kde4_add_plugin(kcm_kpk_settings ${kpk_settings_SRCS})
target_link_libraries(kcm_kpk_settings ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} ${KDE4_KNEWSTUFF2_LIBS})

install(TARGETS kcm_kpk_settings  DESTINATION ${PLUGIN_INSTALL_DIR} )
