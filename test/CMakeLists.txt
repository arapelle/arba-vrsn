find_or_fetch_GTest()

add_cpp_library_basic_tests(GTest::gtest_main
    HEADER_ONLY ${PROJECT_NAME}
    SOURCES
        extract_semantic_version_tests.cpp
        extract_tri_version_tests.cpp
        tri_version_tests.cpp
        tri_version_tag_tests.cpp
        semantic_version_tests.cpp
        project_version_tests.cpp
)
