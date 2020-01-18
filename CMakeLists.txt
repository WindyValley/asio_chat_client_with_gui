cmake_minimum_required(VERSION 3.10)
project(asio_chat LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(. SRC_FILES)
add_executable(chat_client ${SRC_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
message(STATUS "------ GTKMM3_INCLUDE_DIRS:${GTKMM3_INCLUDE_DIRS}")
message(STATUS "------ GTKMM3_LIBRARIES:${GTKMM3_LIBRARIES}")
include_directories(${GTKMM3_INCLUDE_DIRS})
link_directories(${GTKMM3_LIBRARY_DIRS})
list(APPEND FC_DEP_LIBS ${GTKMM3_LIBRARIES})

if(WIN32)
    list(APPEND FC_DEP_LIBS ws2_32)
else(WIN32)
    list(APPEND FC_DEP_LIBS pthread)
endif(WIN32)

find_package(Boost REQUIRED COMPONENTS
    system
)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND FC_DEP_LIBS ${Boost_LIBRARIES})
target_link_libraries(chat_client PUBLIC ${FC_DEP_LIBS})
target_link_options(chat_client PUBLIC "-mwindows")