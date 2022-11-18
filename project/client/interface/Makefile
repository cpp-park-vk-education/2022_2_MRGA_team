TARGET_APP = build/project/client/interface/PartyTime/PartyTime.app/Contents/MacOS/PartyTime
TARGET_TEST = build/tests/interface_tests

.PHONY: all build rebuild check test memtest covtest clean

all: clean check build test

build:
	scripts/build.sh

# check:
# 	./scripts/check.sh

rebuild: clean build

run: build
	./${TARGET_APP}

test: build
	./${TARGET_TEST}

memtest: build
	scripts/memtest.sh

covtest: build
	scripts/coverage.sh

check:
	./scripts/run.sh

clean:
	rm -rf build valgrind.log coverage.info