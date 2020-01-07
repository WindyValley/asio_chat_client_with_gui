cmake_minimum_required(VERSION 3.10)
project(asio_chat LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
message(STATUS "----- GTK3_INCLUDE_DIRS: ${GTK3_INCLUDE_DIRS}")
message(STATUS "----- GKT3_LIBRARIES: ${GTK3_LIBRARIES}")
message(STATUS "----- GTK3_LINK_LIBRARIES: ${GTK3_LINK_LIBRARIES}")
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
list(APPEND FC_DEP_LIBS ${GTK3_LIBRARIES})
list(APPEND FC_DEP_LIBS pthread)

find_package(Boost REQUIRED COMPONENTS
    system
)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND FC_DEP_LIBS ${Boost_LIBRARIES})
add_executable(chat_client
    main.cpp
    Login.cpp
    Window.cpp
)

target_link_libraries(chat_client PUBLIC ${FC_DEP_LIBS})
