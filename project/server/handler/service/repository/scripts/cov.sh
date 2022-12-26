project_dir=$(pwd)

cd build/
lcov -d lib  -t "tests/test_postgres" -o coverage.info -c --include "$project_dir/lib/*"
genhtml -o report coverage.info