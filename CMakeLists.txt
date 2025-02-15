cmake_minimum_required(VERSION 3.20.0)
project(AsciiJuke VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)  
set(CMAKE_CXX_EXTENSIONS OFF) 

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(PROGRAM_SOURCES
  ${SOURCE_DIR}/ui/graphics.hpp
  ${SOURCE_DIR}/ui/graphics.cpp

  ${SOURCE_DIR}/ui/main_menu.hpp
  ${SOURCE_DIR}/ui/main_menu.cpp

)

add_executable(AsciiJuke ${SOURCE_DIR}/main.cpp ${PROGRAM_SOURCES})
target_include_directories(AsciiJuke PUBLIC ${SOURCE_DIR})



set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

if(${CURSES_FOUND})
  include_directories(${CURSES_INCLUDE_DIRS})
  target_link_libraries(AsciiJuke PUBLIC ${CURSES_LIBRARIES})
endif()
