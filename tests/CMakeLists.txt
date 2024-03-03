enable_testing()
include(CTest)

add_executable(
  unit_tests
  test_dataPulse.cpp
)
target_link_libraries(
  unit_tests PRIVATE
)