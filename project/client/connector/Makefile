TARGET=libconnector.a

.PHONY: all build rebuild check memcheck cov_test clean

all: clean check build test memtest cov_test


build:
	scripts/build.sh

rebuild: clean build

clean:
	rm -rf build
