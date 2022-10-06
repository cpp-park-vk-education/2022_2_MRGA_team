TARGET=libconnector.a

.PHONY: all build rebuild check memcheck cov_test clean debug_build

all: clean check build test memtest sanitize cov_test


build:
	scripts/build.sh -D WITH_MEMCHECK=OFF -D WITH_SANITIZE=OFF

debug_build:
	scripts/build.sh -D WITH_MEMCHECK=OFF -D WITH_SANITIZE=OFF -D WITH_DEBUG=ON

rebuild: clean build

test:
	scripts/build.sh -D WITH_TESTING=ON

sanitize:
	scripts/build.sh -D WITH_TESTING=ON -D WITH_SANITIZE=ON

clean:
	rm -rf build
