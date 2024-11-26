
include(cmtk/CppLibraryTests)
include(GoogleTest)

find_package(GTest CONFIG REQUIRED)

add_cpp_library_basic_tests(${PROJECT_NAME} GTest::gtest_main
    SOURCES
        extract_semantic_version_tests.cpp
        extract_tri_version_tests.cpp
        tri_version_tests.cpp
        tri_version_tag_tests.cpp
        semantic_version_tests.cpp
        project_version_tests.cpp
)
