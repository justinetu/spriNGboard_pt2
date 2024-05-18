add_executable(test__01__threads
  test__01__threads.cc
)
target_link_libraries(test__01__threads PRIVATE Catch2::Catch2WithMain pthread)

add_test(NAME    test__01__threads
         COMMAND $<TARGET_FILE:test__01__threads>)

