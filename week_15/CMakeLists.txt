add_executable(test__01__lifetimes
  test__01__lifetimes.cc
)
target_link_libraries(test__01__lifetimes PRIVATE Catch2::Catch2WithMain)

add_test(NAME    test__01__lifetimes
         COMMAND $<TARGET_FILE:test__01__lifetimes>)

