.PHONY:  build test

all: build

docker_run: 
	docker run -it -v "${PWD}:/project" --net=host -v ~/.gitconfig:/etc/gitconfig -v ~/.ssh:/root/.ssh:ro -w "/project" yakwilik/boost_1_81_beta

rebuild: clean build

build:
	scripts/build.sh

clean:
	rm -rf build
