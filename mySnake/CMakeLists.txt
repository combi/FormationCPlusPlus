##
## Cmake minimun version
##
cmake_minimum_required (VERSION 2.6)

##
## Projet Name
##
project (mySnake)

##
## C++ Stantard compilation
##
set(CMAKE_CXX_STANDARD 17)

##
## Binary / Library location
##
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

##
## Flags
##
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -g3 -W -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")

##
## Add Ncurses lib
##
find_package(Curses REQUIRED)

##
## Add include directory.
##
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CURSES_INCLUDE_DIR})

##
## Sources files
##
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

##
## Create binary / Link
##
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
