cmake_minimum_required(VERSION 3.21.3...3.30)
message(STATUS "cmake version: ${CMAKE_VERSION}")
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
project(Pulse)

enable_testing()
include(CTest)

set(BOOST_ROOT "C:/Program Files/boost/boost_1_84_0")
set(BOOST_INCLUDEDIR "C:/Program Files/boost/boost_1_84_0/include")
set(BOOST_LIBRARYDIR "C:/Program Files/boost/boost_1_84_0/lib")
find_package(Boost 1.84.0 REQUIRED COMPONENTS headers log thread chrono filesystem system unit_test_framework)

set(PROJECT_UNIT_TESTS_NAME ${PROJECT_NAME}_unit_tests)

set(UNIT_TESTS_SRC_FILES 
	"${CMAKE_CURRENT_SOURCE_DIR}/tests_main.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/tests_db.cpp"
)

# Build unit tests shared mode
#add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(${PROJECT_UNIT_TESTS_NAME} ${UNIT_TESTS_SRC_FILES})

target_include_directories(${PROJECT_UNIT_TESTS_NAME} PRIVATE ${BOOST_INCLUDE_DIRS})

#target_compile_definitions(${PROJECT_UNIT_TESTS_NAME} PRIVATE "BOOST_TEST_DYN_LINK=1")

target_link_libraries(${PROJECT_UNIT_TESTS_NAME} 
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	${Boost_LIBRARIES}
)

# declares a test with our executable
add_test(NAME UnitsTest COMMAND ${PROJECT_UNIT_TESTS_NAME})