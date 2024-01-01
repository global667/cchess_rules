cmake_minimum_required(VERSION 3.14)

project(cchess_rules LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_library(cchess_rules SHARED
  cchess_rules_global.h
  cchess_rules.cpp
  cchess_rules.h
  types.h
)

target_link_libraries(cchess_rules PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_compile_definitions(cchess_rules PRIVATE CCHESS_RULES_LIBRARY)
