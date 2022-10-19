TARGET=libconnector.a
required_lines_cov=4
required_functions_cov=1

container=yakwilik/cxx:valgrind

.PHONY: all build rebuild check memcheck cov_test clean debug_build  run_docker get_home

all: clean check build test memtest sanitize cov

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

memtest:
	scripts/build.sh -D WITH_TESTING=ON -D WITH_MEMCHECK=ON -D WITH_DEBUG=ON
	scripts/test.sh



sanitize:
	scripts/build.sh -D WITH_TESTING=ON -D WITH_SANITIZE=ON
	scripts/test.sh

clean:
	rm -rf build

run_docker:
	docker run -it -v "${PWD}:/project" -v ~/.gitconfig:/etc/gitconfig -v ~/.ssh:/root/.ssh:ro -w "/project" --rm $(container)

cov: test
	scripts/cov.sh $(required_lines_cov) $(required_functions_cov)

get_home:
	echo "$(HOME)"

some:
	scripts/catfile.sh
