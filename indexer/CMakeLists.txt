SET(CMAKE_CXX_FLAGS "-std=c++11")

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(indexer)

ADD_LIBRARY(libs_parser ../libs/parser/parser.cpp ../libs/parser/parser.h)
ADD_LIBRARY(libs_indexer ../libs/indexer/indexer.cpp ../libs/indexer/indexer.h)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../")

ADD_EXECUTABLE(indexer main.cpp)

TARGET_LINK_LIBRARIES(indexer libs_parser libs_indexer)
