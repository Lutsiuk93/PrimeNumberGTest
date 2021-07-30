enable_testing()

add_executable(PrimeNumberUnitTests PrimeNumberUnitTest.cpp)

target_link_libraries(PrimeNumberUnitTests
  PrimeNumber.Core
  gmock
  gtest_main
)

#include(GoogleTest)
#gtest_discover_tests(hello_test)