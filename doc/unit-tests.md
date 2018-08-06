Compiling/running unit tests
------------------------------------

Unit tests will be automatically compiled if dependencies were met in configure
and tests weren't explicitly disabled.

After configuring, they can be run with 'make check'.

To run the ittriumd tests manually, launch src/test/test_ittrium .

To add more ittriumd tests, add `BOOST_AUTO_TEST_CASE` functions to the existing
.cpp files in the test/ directory or add new .cpp files that
implement new BOOST_AUTO_TEST_SUITE sections.

To run the ittrium-qt tests manually, launch src/qt/test/ittrium-qt_test

To add more ittrium-qt tests, add them to the `src/qt/test/` directory and
the `src/qt/test/test_main.cpp` file.
