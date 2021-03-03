cmake_minimum_required(VERSION 3.14...3.19 FATAL_ERROR)
project(Supermarket.basic)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    weasel
    GIT_REPOSITORY https://github.com/getweasel/weasel-cpp.git
    GIT_TAG        origin/main
)
FetchContent_MakeAvailable(weasel)

add_executable(${PROJECT_NAME}
    main.cpp
    SuperMarketTest.cpp
)
find_library(Supermarket.model model ../../model)
target_link_libraries(${PROJECT_NAME} PUBLIC Supermarket.model weasel_client)
add_test(NAME Supermarket.basic COMMAND Supermarket.basic)
