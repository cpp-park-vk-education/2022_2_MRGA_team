TARGET=libconnector.a
host_dir=
container=yakwilik/cxx_project:27102022

.PHONY: all build rebuild check memcheck cov_test clean debug_build  run_docker get_home

all: clean check build test memtest sanitize cov_test cov

check:
	scripts/check.sh


build:
	scripts/build.sh -D WITH_MEMCHECK=OFF -D WITH_SANITIZE=OFF

debug_build:
	scripts/build.sh -D WITH_MEMCHECK=OFF -D WITH_SANITIZE=OFF -D WITH_DEBUG=ON

rebuild: clean build

test:
	scripts/build.sh -D WITH_TESTING=ON -D WITH_DEBUG=ON
	scripts/test.sh

sanitize:
	scripts/build.sh -D WITH_TESTING=ON -D WITH_SANITIZE=ON

clean:
	rm -rf build

run_docker:
	docker run -it -v "${PWD}:/project" --net=host -v ~/.gitconfig:/etc/gitconfig -v ~/.ssh:/root/.ssh:ro -w "/project" --rm $(container)

cov: test
	scripts/cov.sh 10 10

get_home:
	echo "$(HOME)"
