cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

# Add FTXUI
include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v4.0.0
)
FetchContent_MakeAvailable(ftxui)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/unit_test.cpp
        src/espresso_based.cpp
        src/cappuccino.cpp
        src/mocha.cpp
)
target_link_libraries(main
        GTest::GTest
        GTest::Main
        ftxui::screen
        ftxui::dom
        ftxui::component
)