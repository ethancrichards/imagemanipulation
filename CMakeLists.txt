cmake_minimum_required(VERSION 3.3)
project(P4_ImageEditingInQt)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(EXECUTABLE_NAME "${PROJECT_NAME}")
set(SOURCES main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

#set(CMAKE_AUTOMOC ON)

find_package(Qt4 REQUIRED QtGui)
find_package(Qt4 REQUIRED QtCore)

# Compiles environment, finding include directories and setting library variables.
INCLUDE(${QT_USE_FILE})

add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${EXECUTABLE_NAME} ${QT_LIBRARIES} QtCore)
