cmake_minimum_required(VERSION 3.0.0)
project(MuseSDK VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/externals/libblepp/cmake/modules)

find_package(Bluez REQUIRED)

add_executable(MuseSDK ./src/main.cpp)
add_subdirectory(externals/libblepp)

message(STATUS ${BLUEZ_INCLUDE_DIRS})

include_directories(${BLUEZ_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PUBLIC externals/libblepp)
target_link_directories(${PROJECT_NAME} PRIVATE externals/libblepp)
target_link_libraries(${PROJECT_NAME} ble++ ${BLUEZ_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
