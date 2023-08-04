cmake_minimum_required(VERSION 3.23.2)

project(boost_mysql_data_integration LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.80.0 REQUIRED COMPONENTS headers date_time filesystem system log)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(Threads REQUIRED)

find_package(OpenSSL REQUIRED)

# Database integration
add_subdirectory(repository)

include_directories(repository/)

add_subdirectory(unittests)

add_executable(boost_mysql_data_integration main.cpp)

target_link_libraries(boost_mysql_data_integration PRIVATE
    Boost::headers Threads::Threads OpenSSL::Crypto OpenSSL::SSL
    ${Boost_LIBRARIES}
    repository
)

