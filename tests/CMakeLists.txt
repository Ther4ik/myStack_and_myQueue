# MSVC: та же библиотека времени выполнения (CRT), что и у проекта
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/googletest
                 ${CMAKE_BINARY_DIR}/googletest EXCLUDE_FROM_ALL)

add_executable(run_tests
  stack_tests.cpp
  queue_tests.cpp
  rooted_tree_tests
)

target_link_libraries(run_tests PRIVATE containers GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests)