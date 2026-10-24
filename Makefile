BUILD_DIR  ?= build
BUILD_TYPE ?= Release
JOBS       ?= $(shell sysctl -n hw.ncpu 2>/dev/null || nproc)

.PHONY: all configure build run clean

all: build

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	ln -sf $(BUILD_DIR)/compile_commands.json compile_commands.json

build: configure
	cmake --build $(BUILD_DIR) -j $(JOBS)

# Pass a filter through, e.g. `make run ARGS="2025 1"`.
run: build
	bin/run.sh $(ARGS)

clean:
	rm -rf $(BUILD_DIR)
