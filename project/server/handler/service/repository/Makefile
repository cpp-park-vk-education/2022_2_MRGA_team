DOCKERFILE=./Dockerfile
IMAGE_NAME=mashanab/gcc_linters_valgrind_cmake_gtest
CONTEXT=.


.PHONY: docker_build docker_push docker_run rebuild  build debug test clean debug_build format memcheck sanitize

all: test cov format check

docker_build: $(DOCKERFILE)
	docker build -f $(DOCKERFILE) -t $(IMAGE_NAME) $(CONTEXT)

docker_push:
	docker push $(IMAGE_NAME)

docker_run: 
	docker run --rm -v "$(PWD):/Project" -w /Project -it $(IMAGE_NAME) bash

test: clean
	scripts/build.sh -D WITH_TESTING=ON -D WITH_DEBUGING=ON -D WITH_MEMCHECK=OFF -D WITH_SANITIZE=OFF
	scripts/test.sh

sanitize: clean
	scripts/build.sh -D WITH_TESTING=ON -D WITH_SANITIZE=ON WITH_DEBUGING=OFF -D WITH_MEMCHECK=OFF

memcheck: clean
	scripts/build.sh -D WITH_TESTING=ON -D WITH_SANITIZE=OFF WITH_DEBUGING=OFF -D WITH_MEMCHECK=ON
	scripts/memcheck.sh
	
clean:
	scripts/clean.sh

check:
	scripts/check.sh

rebuild: clean build

build:
	scripts/build.sh -D WITH_MEMCHECK=OFF -D WITH_SANITIZE=OFF -D WITH_DEBUGING=OFF WITH_TESTING=OFF

debug_build:
	scripts/build.sh -D WITH_MEMCHECK=OFF -D WITH_SANITIZE=OFF -D WITH_DEBUGING=ON  WITH_TESTING=OFF

cov: test
	scripts/cov.sh

format:
	clang-format -i lib/include/* lib/src/* lib/interface/*
