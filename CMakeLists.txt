cmake_minimum_required(VERSION 3.21.3...3.30)
message(STATUS "cmake version: ${CMAKE_VERSION}")
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(DataPulse VERSION 1.0 DESCRIPTION "Full stack development project" LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w44101")

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

#set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} C:/Program Files/MySQL/MySQL Server 8.3 C:/Program Files/MySQL/MySQL/MySQL Connector C++ 8.3")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "C:/Program Files/MySQL/MySQL/MySQL Connector C++ 8.3")
# This creates a config.h in the build directory corresponding to this source directory
configure_file(config.h.in config.h @ONLY)

set(BOOST_ROOT "C:/Program Files/boost/boost_1_84_0")
set(BOOST_INCLUDEDIR "C:/Program Files/boost/boost_1_84_0/include")
set(BOOST_LIBRARYDIR "C:/Program Files/boost/boost_1_84_0/lib")
set(Boost_USE_DEBUG_LIBS        ON)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.84.0 REQUIRED COMPONENTS headers log thread chrono)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
 endif()

 set(mysql-concpp_FIND_VERBOSE TRUE)
 find_package(mysql-concpp)
 if (mysql-concpp_FOUND)
    set(MYSQL_CONCPP_ROOT_DIR "C:/Program Files/MySQL/MySQL/MySQL Connector C++ 8.3")
    set(MYSQL_CONCPP_RUNTIME_LIBRARY_DIRS "C:/Program Files/MySQL/MySQL/MySQL Connector C++ 8.3/lib64")
    set(mysql-concpp_PLUGIN_DIR "C:/Program Files/MySQL/MySQL/MySQL Connector C++ 8.3/lib64/plugin")
    message(STATUS "found mysql-concpp module config version: ${MYSQL_CONCPP_VERSION}")
    message(STATUS "mysql runtime dirs: ${MYSQL_CONCPP_RUNTIME_LIBRARY_DIRS}")
    include_directories("C:/Program Files/MySQL/MySQL/MySQL Connector C++ 8.3/include")
    link_directories("C:/Program Files/MySQL/MySQL/MySQL Connector C++ 8.3/lib64")
 endif()

add_subdirectory(docs)
#add_subdirectory(tests)

set(PROJECT_HEADERS 
                    
                    )

set(PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp
                    )

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
message (STATUS "building using GNU compiler")
add_compile_options(
  -Wall                # Enables most warnings.
  -Wextra              # Enables an extra set of warnings.
  -pedantic            # Strict compliance to the standard is not met.
  -Wcast-align         # Pointer casts which increase alignment.
  -Wcast-qual          # A pointer is cast to remove a type qualifier, or add an unsafe one.
  -Wconversion         # Implicit type conversions that may change a value.
  -Wformat=2           # printf/scanf/strftime/strfmon format string anomalies.
  -Wnon-virtual-dtor   # Non-virtual destructors are found.
  -Wold-style-cast     # C-style cast is used in a program.
  -Woverloaded-virtual # Overloaded virtual function names.
  -Wsign-conversion    # Implicit conversions between signed and unsigned integers.
  -Wshadow             # One variable shadows another.
  -Wswitch-enum        # A switch statement has an index of enumerated type and lacks a case.
  -Wundef              # An undefined identifier is evaluated in an #if directive.
  -Wunused             # Enable all -Wunused- warnings.
  -Wdisabled-optimization       # GCC’s optimizers are unable to handle the code effectively.
  -Weffc++                      # Warnings related to guidelines from Scott Meyers’ Effective C++ books.
  -Wlogical-op                  # Warn when a logical operator is always evaluating to true or false.
  -Wsign-promo                  # Overload resolution chooses a promotion from unsigned to a signed type.
  -Wswitch-default              # A switch statement does not have a default case.
  -Wredundant-decls             # Something is declared more than once in the same scope.
  $<$<CONFIG:DEBUG>:-g3>
  $<$<CONFIG:DEBUG>:-Og>
   $<$<CONFIG:DEBUG>:-O2>
  $<$<CONFIG:RELEASE>:-O3>
  $<$<CONFIG:RELEASE>:-Os>
)
endif()

add_compile_definitions(
  $<$<CONFIG:DEBUG>:DEBUG>
)

add_executable(DataPulse ${PROJECT_HEADERS} ${PROJECT_SOURCES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Adding compiler definations for build using msvc compiler Windows 10. ")
target_compile_definitions(DataPulse PUBLIC 
    /permissive- # Specify standards conformance mode to the compiler.
    /W4          # Enable level 4 warnings.
    /w14062      # Enumerator 'identifier' in a switch of enum 'enumeration' is not handled.
    /w14242      # The types are different, possible loss of data. The compiler makes the conversion.
    /w14254      # A larger bit field was assigned to a smaller bit field, possible loss of data.
    /w14263      # Member function does not override any base class virtual member function.
    /w14265      # 'class': class has virtual functions, but destructor is not virtual.
    /w14287      # 'operator': unsigned/negative constant mismatch.
    /w14289      # Loop control variable is used outside the for-loop scope.
    /w14296      # 'operator': expression is always false.
    /w14311      # 'variable' : pointer truncation from 'type' to 'type'.
    /w14545      # Expression before comma evaluates to a function which is missing an argument list.
    /w14546      # Function call before comma missing argument list.
    /w14547      # Operator before comma has no effect; expected operator with side-effect.
    /w14549      # Operator before comma has no effect; did you intend 'operator2'?
    /w14555      # Expression has no effect; expected expression with side-effect.
    /w14619      # #pragma warning: there is no warning number 'number'.
    /w14640      # 'instance': construction of local static object is not thread-safe.
    /w14826      # Conversion from 'type1' to 'type2' is sign-extended.
    /w14905      # Wide string literal cast to 'LPSTR'.
    /w14906      # String literal cast to 'LPWSTR'.
    /w14928      # Illegal copy-initialization; applied more than one user-defined conversion.
)
endif()

target_include_directories(DataPulse PUBLIC
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(DataPulse PUBLIC
   Boost::headers
   ${Boost_LIBRARIES} 
   mysql::concpp
)

