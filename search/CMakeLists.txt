SET(CMAKE_CXX_FLAGS "-std=c++11")

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(search)

ADD_LIBRARY(libs_indexer ../libs/indexer/indexer.cpp ../libs/indexer/indexer.h)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../")

ADD_EXECUTABLE(search main.cpp)

TARGET_LINK_LIBRARIES(search libs_indexer)
