cmake_minimum_required(VERSION 3.7...3.30)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(DataPulse VERSION 1.0 DESCRIPTION "Very nice project" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(default_build_type "RelWithDebInfo")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
# This creates a config.h in the build directory corresponding to this source directory
configure_file(config.h.in config.h @ONLY)

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

find_package(hiredis)

add_subdirectory(docs)
add_subdirectory(tests)

set(PROJECT_HEADERS src/RedisBuilder.h)
set(PROJECT_SOURCES src/main.cpp)

add_executable(DataPulse ${PROJECT_HEADERS} ${PROJECT_SOURCES})

target_include_directories(DataPulse PUBLIC "${CMAKE_CURRENT_BINARY_DIR}" )

target_link_libraries(DataPulse PRIVATE
    Boost::headers Threads::Threads OpenSSL::Crypto OpenSSL::SSL
    ${Boost_LIBRARIES}
    hiredis
    libhiredis_ssl
)
target_compile_features(DataPulse PUBLIC cxx_std_11)
