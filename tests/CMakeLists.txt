enable_testing()
include(AddCatch2)
include(CTest)
include(Catch)

add_executable(
  unit_tests
  test_dataPulse.cpp
)
target_link_libraries(
  unit_tests PRIVATE Catch2::Catch2WithMain
)

catch_discover_tests(unit_tests)
