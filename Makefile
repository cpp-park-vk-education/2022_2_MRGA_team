.PHONY:  build test

all: build

docker_run:
	docker run -it -v "${PWD}:/project" --net=host -v ~/.gitconfig:/etc/gitconfig -v ~/.ssh:/root/.ssh:ro -w "/project" yakwilik/mrga_backend

rebuild: clean build

build:
	mkdir build && cd build && cmake .. && cmake --build .

clean:
	rm -rf build

run: build
	cd build/project && ./server

build-up:
	docker compose up -d --build

compose-log:
	docker compose logs -f

compose-down:
	docker compose down -v

local:
	mkdir -p local_build && cd local_build && cmake .. && cmake --build .

local-run: local
	./local_build/project/server/server 0.0.0.0 8081 0.0.0.0 5432
