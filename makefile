CC := clang
BUILD_DIR := build
HEADER_DIR := include
SRC_DIR := src
DOMAIN_HEADER_DIRS := $(wildcard $(HEADER_DIR)/*)
DOMAIN_SRC_DIRS := $(wildcard $(SRC_DIR)/*)
CFLAGS := -g -I$(HEADER_DIR) $(foreach dir,$(DOMAIN_HEADER_DIRS),-I$(dir)) \
          -std=c99 -Wall -Wextra -pedantic -Wconversion -Wno-unused-function
CLANGD_FLAGS := $(filter-out -Wno-unused-function,$(CFLAGS))
HEADERS := $(wildcard $(HEADER_DIR)/*.h) $(wildcard $(HEADER_DIR)/*/*.h)
SRC := $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)
SRC += main.c
TARGET := program
.DEFAULT_GOAL := all

ifeq ($(OS),Windows_NT)
	EXE := .exe
else
	EXE :=
endif

.PHONY: all clean

all: compile_flags.txt $(BUILD_DIR)/$(TARGET)$(EXE)

$(BUILD_DIR):
	@echo "Creating build directory (./$(BUILD_DIR))"
	mkdir -p "$(BUILD_DIR)"

$(BUILD_DIR)/$(TARGET)$(EXE): $(SRC) $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $@

compile_flags.txt:
	@echo "Generating $@ for Clangd..."
	@rm -f $@
	$(foreach flag,$(CLANGD_FLAGS),echo '$(flag)' >> $@;)

clean:
	rm -rf "$(BUILD_DIR)"
