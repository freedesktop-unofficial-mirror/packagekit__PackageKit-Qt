 
## install the cmake files

file( GLOB cmakeFiles FindQPackageKit.cmake )
# FIXME remove safely /usr/share
set(module_install_dir ${CMAKE_ROOT}/Modules )

install( FILES ${cmakeFiles} 
         DESTINATION ${module_install_dir}  )


# with cmake 2.6 and above create and install a man page for the kdelibs cmake modules
# (cmake 2.4 doesn't support creating documentation for cmake modules in custom directories)
# if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" GREATER "2.5")
#    add_custom_target(KDECMakeModulesManPage ALL COMMAND ${CMAKE_COMMAND} -DCMAKE_MODULE_PATH=${CMAKE_CURRENT_SOURCE_DIR} --help-custom-modules ${CMAKE_CURRENT_BINARY_DIR}/kdecmake.1)
#    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kdecmake.1 DESTINATION "${MAN_INSTALL_DIR}/man1")
# endif("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" GREATER "2.5")
