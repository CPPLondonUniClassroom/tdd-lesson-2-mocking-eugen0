cmake_minimum_required(VERSION 3.11)
project(Blockbuster)

set(CMAKE_CXX_STANDARD 17)

add_executable(Blockbuster main.cpp include/interface/IRentable.h include/Video.h src/Video.cpp include/interface/ICustomer.h include/Money.h)
target_include_directories(Blockbuster PRIVATE include)

add_executable(TestBlockbuster test/testmain.cpp test/catch.hpp test/trompeloeil.hpp)
target_include_directories(Blockbuster PRIVATE include)