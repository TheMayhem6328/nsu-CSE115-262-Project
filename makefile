CC := clang
CFLAGS := -std=c99 -Wall -Wextra -pedantic
SRC := types.c admin.c manager.c player.c team.c session.c file.c main.c
HEADERS := types.h admin.h manager.h player.h team.h session.h file.h
BUILD_DIR := build
TARGET := program
.DEFAULT_GOAL := all

ifeq ($(OS),Windows_NT)
	EXE := .exe
else
	EXE :=
endif

.PHONY: all clean

all: $(BUILD_DIR)/$(TARGET)$(EXE)

$(BUILD_DIR):
	mkdir -p "$(BUILD_DIR)"

$(BUILD_DIR)/$(TARGET)$(EXE): $(SRC) $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $@

# Cleanup
clean:
	rm -rf "$(BUILD_DIR)"
