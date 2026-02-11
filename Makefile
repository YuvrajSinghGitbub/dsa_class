# Compiler and Flags
CC = clang
# -Iinclude allows using <dsa/header.h>
# -MMD -MP generates dependency files so headers recompile correctly
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic -g -Iinclude -MMD -MP
LDFLAGS = 

# Directories
SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = build/bin
TEST_DIR = tests

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Target Library name
TARGET_LIB = $(BIN_DIR)/libdsa.a

# Default target
all: $(TARGET_LIB)

# Link the static library
$(TARGET_LIB): $(OBJS) | $(BIN_DIR)
	ar rcs $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean artifacts
clean:
	rm -rf build

# Helper for Neovim/Clangd (requires 'bear' installed, or use a generator)
# usage: make compile_commands
compile_commands: clean
	bear -- make all

.PHONY: all clean compile_commands

-include $(OBJS:.o=.d)
