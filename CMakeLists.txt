cmake_minimum_required(VERSION 3.22.1)

project(DataPulse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
add_subdirectory(src)
add_subdirectory(docs)
add_subdirectory(tests)

add_executable(DataPulse src/main.cpp)

target_link_libraries(DataPulse PRIVATE
    Boost::headers Threads::Threads OpenSSL::Crypto OpenSSL::SSL
    ${Boost_LIBRARIES}
)
