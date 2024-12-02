
include(cmtk/CppLibraryTests)
include(GoogleTest)

find_package(GTest CONFIG REQUIRED)

add_cpp_library_basic_tests(${PROJECT_NAME} GTest::gtest_main
    SOURCES
        extract_semver_tests.cpp
        extract_numver_tests.cpp
        numver_tests.cpp
        vtag_tests.cpp
        semver_tests.cpp
        project_version_tests.cpp
)
