CC = clang
CFLAGS = -std=c89
SRC = types.h main.c
BUILD_DIR = build/
TARGET = program


# Platform detection
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        DETECTED_OS := Linux
    endif
    ifeq ($(UNAME_S),Darwin)
        DETECTED_OS := macOS
    endif
endif


# Phony
.PHONY: all build-current build-windows build-linux clean

# Build all platform targets
build:
	@echo Building all
	make build-windows
	make build-linux


# Make build for current platform 
build-current:
	@echo "Current OS: $(DETECTED_OS)"
ifeq ($(DETECTED_OS),Windows)
	make build-windows
endif
ifeq ($(DETECTED_OS),Linux)
	make build-linux
endif
ifeq ($(DETECTED_OS),macOS)
	make build-linux
endif


# Platform-specific builds
build-windows: $(SRC) | $(BUILD_DIR)
	@echo "Building Windows"
	$(CC) $(CFLAGS) main.c -o $(BUILD_DIR)$(TARGET).exe

build-linux: $(SRC) | $(BUILD_DIR)
	@echo "Building Linux"
	$(CC) $(CFLAGS) main.c -o $(BUILD_DIR)$(TARGET).o


# Make build directory if it doesn't exist 
$(BUILD_DIR):
	mkdir -p "$(BUILD_DIR)"


# Cleanup
clean:
	rm -rf "$(BUILD_DIR)"