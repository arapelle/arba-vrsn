cmake_minimum_required(VERSION 3.26)

# CMAKE INCLUDES

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/external/cmake/)
include(CMakePrintHelpers)
include(cmtk/CppLibraryProject)

# CONFIGURATION

disable_in_source_build()
set_build_type_ifndef()

# C++ PROJECT

set_project_name(NAMESPACE "arba" BASE_NAME "vrsn")
string(TIMESTAMP configure_datetime "%Y%m%d-%H%M%S" UTC)
set_project_semantic_version("0.2.0"
    PRE_RELEASE "dev"
    BUILD_METADATA "${configure_datetime}"
)

project(${PROJECT_NAME}
        VERSION ${PROJECT_VERSION}
        DESCRIPTION "A C++ library providing version classes."
        HOMEPAGE_URL "https://github.com/arapelle/arba-vrsn"
        LANGUAGES CXX)
message(STATUS "PROJECT : ${PROJECT_NAME} ${PROJECT_SEMANTIC_VERSION} ${CMAKE_BUILD_TYPE}")
include(CTest)

# Add external dependencies (submodules and fetch/find packages)

add_subdirectory(external)

# C++ LIBRARY

## Generated/Configured headers:
configure_headers(configured_headers
    FILES
        include/${PROJECT_NAMESPACE}/${PROJECT_BASE_NAME}/version.hpp.in
)

## Headers:
set(headers
    include/arba/vrsn/string/string_conversion.hpp
    include/arba/vrsn/concepts/semantic_version.hpp
    include/arba/vrsn/concepts/tri_version.hpp
    include/arba/vrsn/is_compatible_with.hpp
    include/arba/vrsn/semantic_version.hpp
    include/arba/vrsn/tri_version.hpp
    include/arba/vrsn/tri_version_tag.hpp
    include/arba/vrsn/_private/extract_semantic_version.hpp
    include/arba/vrsn/_private/extract_tri_version.hpp
)

## Add C++ library
add_cpp_library(
    HEADER_ONLY ${PROJECT_NAME}
    HEADERS ${headers} ${configured_headers}
    CXX_STANDARD 20
)

## Install C++ library:
install_cpp_library(
    HEADER_ONLY ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
)

## Install project package
install_library_package(${PROJECT_NAME} INPUT_PACKAGE_CONFIG_FILE cmake/config/package-config.cmake.in)
install_uninstall_script(${PROJECT_NAME} FILENAME uninstall.cmake)

## Add examples:
option_or_set_ifdef(BUILD_${PROJECT_NAME}_EXAMPLES "Build ${PROJECT_NAME} examples or not" OFF BUILD_arba-arba_EXAMPLES)
if(BUILD_${PROJECT_NAME}_EXAMPLES)
    add_subdirectory(example)
endif()

## Add tests:
option_or_set_ifdef(BUILD_${PROJECT_NAME}_TESTS "Build ${PROJECT_NAME} tests or not" OFF BUILD_arba-arba_TESTS)
if(BUILD_${PROJECT_NAME}_TESTS AND BUILD_TESTING)
    add_subdirectory(test)
endif()
