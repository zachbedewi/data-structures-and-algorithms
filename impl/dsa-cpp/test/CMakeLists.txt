include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

# --- variant ---
add_executable(variant_test variant_test.cpp)
target_link_libraries(variant_test PRIVATE
  myproject::myproject_warnings
  myproject::myproject_options
  variant
  Catch2::Catch2WithMain)
catch_discover_tests(variant_test TEST_PREFIX "variant.")
