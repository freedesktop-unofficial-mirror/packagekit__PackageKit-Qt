project(packagekit-qt)

if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	SET(LIB_SUFFIX "64")
ELSE(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	SET(LIB_SUFFIX "")
ENDIF(${CMAKE_SIZEOF_VOID_P} EQUAL 8)

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

install(TARGETS
	packagekit-qt
	DESTINATION
	lib${LIB_SUFFIX}
	)

install(FILES
	Daemon.h
	Transaction.h
	Exit.h
	Actions.h
	Error.h
	Exit.h
	Provides.h
	Restart.h
	Role.h
	SignatureType.h
	Status.h
	Groups.h
	QPackageKit
	DESTINATION
	include/packagekit-qt)

add_subdirectory(modules)

#endif
