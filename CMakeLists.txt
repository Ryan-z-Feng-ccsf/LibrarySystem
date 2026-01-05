cmake_minimum_required(VERSION 3.31)
project(LibraryManagement)

set(CMAKE_CXX_STANDARD 20)

add_executable(LibraryManagement main.cpp
        include/User.h
        src/Reader.cpp
        include/Reader.h
        src/Book.cpp
        include/Book.h
        src/BorrowReturn.cpp
        include/BorrowReturn.h
        src/Ranking.cpp
        include/Ranking.h
        src/Find.cpp
        include/Find.h
        src/Admin.cpp
        include/Admin.h)
