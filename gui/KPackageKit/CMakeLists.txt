find_package(KDE4Internal REQUIRED)

set(kpackagekit_SRCS
    main.cpp
    kpk.cpp
    PkNotify.cpp
)

kde4_add_executable(kpackagekit ${kpackagekit_SRCS})

target_link_libraries(kpackagekit ${KDE4_KDEUI_LIBS} ${KDE4_KNOTIFY_LIBS} ${QPACKAGEKIT_LIB})

install(TARGETS kpackagekit ${INSTALL_TARGETS_DEFAULT_ARGS})
# keep the KPackageKit dir upper cased for notification
install(FILES KPackageKit.notifyrc DESTINATION ${DATA_INSTALL_DIR}/KPackageKit)