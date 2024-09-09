cmake_minimum_required(VERSION 3.26)

# CMAKE INCLUDES

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/external/cmake/)
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
add_cpp_library(${PROJECT_NAME} HEADER_ONLY
  HEADERS ${headers} ${configured_headers}
  CXX_STANDARD 20
  DEFAULT_WARNING_OPTIONS
)
add_library("${PROJECT_NAMESPACE}::${PROJECT_BASE_NAME}" ALIAS ${PROJECT_NAME})

## Add tests:
add_test_subdirectory_if_build(test)

## Add examples:
add_example_subdirectory_if_build(example)

# C++ INSTALL

## Install C++ library:
install_cpp_libraries(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets)

## Install project package
install_library_package(${PROJECT_NAME} INPUT_PACKAGE_CONFIG_FILE cmake/config/package-config.cmake.in)
install_uninstall_script(${PROJECT_NAME})
