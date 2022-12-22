# cd build/
cp -rf configs build/tests
ctest -VV --test-dir build
# cd ..