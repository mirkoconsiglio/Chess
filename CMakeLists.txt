cmake_minimum_required(VERSION 3.17)
project(Chess)

set(CMAKE_CXX_STANDARD 20)

add_executable(Chess general.h main.cpp chess.cpp chess.h interface.cpp interface.h piece.cpp piece.h board.cpp board.h shogi.cpp shogi.h engine.cpp engine.h)