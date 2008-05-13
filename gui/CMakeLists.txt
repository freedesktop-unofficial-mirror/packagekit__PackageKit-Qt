cmake_minimum_required(VERSION 2.6)

project(KPackageKit)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
# TODO fix link_directories
## ${CMAKE_BINARY_DIR}
link_directories( /home/daniel/projetos/PackageKit/QPackageKit/lib/ )
add_definitions(${QT_DEFINITIONS} ${KDE_DEFINITIONS})
include_directories( ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES} ${KDE4_KIO_INCLUDES})

add_subdirectory( ui )
