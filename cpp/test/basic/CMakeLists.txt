cmake_minimum_required(VERSION 3.8)
project(Supermarket.basic)

set(CONAN_CMAKE_SILENT_OUTPUT ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
find_package("weasel" QUIET)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    main.cpp
    SuperMarketTest.cpp
)
find_library(Supermarket.model model ../../model)
target_link_libraries(${PROJECT_NAME} PUBLIC Supermarket.model weasel::client)
add_test(NAME Supermarket.basic COMMAND Supermarket.basic)
