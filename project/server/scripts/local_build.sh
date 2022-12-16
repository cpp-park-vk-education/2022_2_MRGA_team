mkdir -p local_build/
cd local_build/
cmake "$@" ..
cmake --build .
cd ..
