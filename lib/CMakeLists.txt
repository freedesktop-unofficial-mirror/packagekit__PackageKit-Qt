cmake_minimum_required(VERSION 2.4.8)

project(packagekit-qt)

if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	SET(LIB_SUFFIX "64")
ELSE(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	SET(LIB_SUFFIX "")
ENDIF(${CMAKE_SIZEOF_VOID_P} EQUAL 8)

find_package(Qt4 REQUIRED)
add_definitions(${QT_DEFINITIONS})

include(FindPkgConfig)
pkg_check_modules(POLICYKIT polkit-dbus)

include_directories(
${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}
  ${QT_INCLUDES}
  ${POLICYKIT_INCLUDE_DIRS}
)

set( PK_LIB_SRCS
	CentralProxy.cpp
	Daemon.cpp
	Package.cpp
	PolkitClient.cpp
	Transaction.cpp
	TransactionProxy.cpp
)
# 	SignatureType.cpp
# 	Status.cpp
# 	Groups.cpp
# )

# qt4_automoc(${PK_LIB_SRCS})

set( PK_SRCS
	CentralProxy.h
	Daemon.h
	Package.h
	PolkitClient.h
	Transaction.h
	TransactionProxy.h
	Error.h
	Exit.h
	Actions.h
	Provides.h
	Restart.h
	Role.h
	SignatureType.h
	Status.h
	Groups.h
)

QT4_WRAP_CPP( Pk_MOC_SRCS ${PK_SRCS} )

# set( packagekit-qt_MOC_SRCS
# 	CentralProxy.moc
# 	Daemon.moc
# 	Package.moc
# 	PolkitClient.moc
# 	Transaction.moc
# 	TransactionProxy.moc
# 	Error.moc
# 	Exit.moc
# 	Actions.moc
# 	Provides.moc
# 	Restart.moc
# 	Role.moc
# 	SignatureType.moc
# 	Status.moc
# 	Groups.moc
# )

add_library(packagekit-qt SHARED ${Pk_MOC_SRCS} ${PK_LIB_SRCS})
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
        CentralProxy.h
	TransactionProxy.h
	Daemon.h
	Transaction.h
	Package.h
	Exit.h
	Actions.h
	Error.h
	Enum.h
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
