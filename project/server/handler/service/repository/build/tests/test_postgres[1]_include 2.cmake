if(EXISTS "/Project/build/tests/test_postgres[1]_tests.cmake")
  include("/Project/build/tests/test_postgres[1]_tests.cmake")
else()
  add_test(test_postgres_NOT_BUILT test_postgres_NOT_BUILT)
endif()
