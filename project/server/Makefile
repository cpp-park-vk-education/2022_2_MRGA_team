.PHONY:  build test

all: build

docker_run:
	docker run -it -v "${PWD}:/project" --net=host -v ~/.gitconfig:/etc/gitconfig -v ~/.ssh:/root/.ssh:ro -w "/project" yakwilik/mrga_backend

rebuild: clean build

build:
	scripts/build.sh

clean:
	rm -rf build

run: build
	cd build && ./server

build-up:
	docker compose up -d --build

compose-log:
	docker compose logs -f

compose-down:
	docker compose down -v
