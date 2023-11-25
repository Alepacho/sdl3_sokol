cmake_minimum_required(VERSION 3.27)

set(PROJECT_NAME "SDL3_Sokol")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME} C CXX)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rdparty/SDL/)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/3rdparty/SDL/include/
    ${CMAKE_CURRENT_LIST_DIR}/3rdparty/sokol/
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    SDL3::SDL3
    OpenGL::GL
)
