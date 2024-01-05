cmake_minimum_required(VERSION 3.26)

project(basic_cmake_project)

add_executable(${PROJECT_NAME} basic_cmake_project.cpp)
# Find package arba-vrsn:
find_package(arba-vrsn 0.1.0 CONFIG REQUIRED)
# Use arba-vrsn release header-only target:
target_link_libraries(${PROJECT_NAME} PRIVATE arba-vrsn)
