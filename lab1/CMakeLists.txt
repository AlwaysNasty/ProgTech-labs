cmake_minimum_required(VERSION 3.16)
project(lab1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab1
    main.cpp
    Base.cpp
    Book.cpp
    Textbook.cpp
    Stationery.cpp
    Keeper.cpp
    KeeperException.cpp
)
