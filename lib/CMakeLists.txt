project(packagekit-qt)

set(CMAKE_MODULE_PATH ${packagekit-qt_SOURCE_DIR}/cmake/modules)

find_package(Qt4 REQUIRED)

include(FindPkgConfig)
pkg_check_modules(POLICYKIT polkit-dbus)

include_directories(
  ${QT_INCLUDES}
  ${POLICYKIT_INCLUDE_DIRS}
)

set( packagekit-qt_LIB_SRCS
	CentralProxy.cpp
	Daemon.cpp
	Package.cpp
	PolkitClient.cpp
	Transaction.cpp
	TransactionProxy.cpp
)

add_library(packagekit-qt SHARED ${packagekit-qt_LIB_SRCS})
set_target_properties( packagekit-qt PROPERTIES VERSION 0.1 SOVERSION 0 )

target_link_libraries(packagekit-qt
  ${QT_QTCORE_LIBRARY}
)

