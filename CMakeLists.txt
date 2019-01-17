cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

set(GRAPENLP_VERSION_MAJOR 2)
set(GRAPENLP_VERSION_MINOR 4)
set(GRAPENLP_VERSION_PATCH 0)

if (NOT ANDROID_NDK_TOOLCHAIN_INCLUDED)
    configure_file(${CMAKE_SOURCE_DIR}/LICENSE
            ${CMAKE_BINARY_DIR}/debian/copyright)
    configure_file(${CMAKE_SOURCE_DIR}/CHANGES
            ${CMAKE_BINARY_DIR}/debian/changelog.Debian)
    execute_process(COMMAND gzip -9 -c ${CMAKE_BINARY_DIR}/debian/changelog.Debian
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/debian
            OUTPUT_FILE "${CMAKE_BINARY_DIR}/debian/changelog.Debian.gz")
endif (NOT ANDROID_NDK_TOOLCHAIN_INCLUDED)

add_subdirectory(src)
