cmake_minimum_required(VERSION 3.21.3...3.30)
message(STATUS "cmake version: ${CMAKE_VERSION}")
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
project(Documentation)
# Require dot, treat the other components as optional
set(DOXYGEN_PROJECT_BRIEF "String with spaces")
set(DOXYGEN_GENERATE_TREEVIEW YES) # optional. Also works without treeview
set(DOXYGEN_DISABLE_INDEX NO)
set(DOXYGEN_FULL_SIDEBAR NO)
set(DOXYGEN_ HTML_EXTRA_STYLESHEET ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome.css)
set(DOXYGEN_HTML_COLORSTYLE LIGHT) # required with Doxygen >= 1.9.5

find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)

if(NOT DOXYGEN_FOUND)
  message(FATAL_ERROR "Doxygen is needed to build the documentation. Please install it on your system")
  else()
     message(STATUS "Doxygen found.")

     file(DOWNLOAD https://raw.githubusercontent.com/jothepro/doxygen-awesome-css/v2.3.1/doxygen-awesome.css
     ${CMAKE_CURRENT_LIST_DIR}/doxygen-awesome.css)
     file(DOWNLOAD https://raw.githubusercontent.com/jothepro/doxygen-awesome-css/v2.3.1/doxygen-awesome-sidebar-only.css
          ${CMAKE_CURRENT_LIST_DIR}/doxygen-awesome-sidebar-only.css)

     # add_custom_target(documentation COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/Doxyfile WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
     #                 BYPRODUCTS ${CMAKE_BINARY_DIR}/html/index.html)
     # add_custom_command(
     # TARGET documentation POST_BUILD COMMAND echo "Documentation successfully generated. You can preview at: ${CMAKE_BINARY_DIR}/html/index.html")

     set(DOXYGEN_GENERATE_HTML YES)
     set(DOXYGEN_HTML_OUTPUT ${CMAKE_BINARY_DIR}/html)
     set(DOXYGEN_GENERATE_TREEVIEW YES)
     list(APPEND DOXYGEN_HTML_EXTRA_STYLESHEET ${PROJECT_SOURCE_DIR}/docs/doxygen-awesome.css)
     list(APPEND DOXYGEN_HTML_EXTRA_STYLESHEET ${PROJECT_SOURCE_DIR}/docs/doxygen-awesome-sidebar-only.css)

     doxygen_add_docs(documentation ${PROJECT_SOURCE_DIR}/src COMMENT "Generating documentation")
endif()
