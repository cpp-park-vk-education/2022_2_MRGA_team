TARGET_APP = build/project/client/interface/PartyTime/PartyTime.app/Contents/MacOS/PartyTime
TARGET_TEST = build/tests/interface_tests

.PHONY: all build rebuild check test memtest covtest clean

all: clean check build test

build:
	scripts/build.sh

rebuild: clean build

check:
	./linters/run.sh
# запуск на маке
run:
	./build.sh
	./${TARGET_APP}

test:
	./build.sh
	./${TARGET_TEST}

memtest:
	./build.sh
	./tests/memtest.sh ./${TARGET_TEST}

covtest:
	./build.sh
	./coverage.sh ./${TARGET_TEST}

clean:
	rm -rf build valgrind.log coverage.info