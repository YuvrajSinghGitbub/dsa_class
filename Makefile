CC = clang
# -Iinclude allows main.c to find <dsa/slist.h>
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic -g -Iinclude -MMD -MP

SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = build/bin

# Library Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TARGET_LIB = $(BIN_DIR)/libdsa.a

# App Files
APP_SRC = main.c
APP_BIN = $(BIN_DIR)/app

# Default: Build both
all: $(TARGET_LIB) $(APP_BIN)

# 1. Compile the Library (Archive)
$(TARGET_LIB): $(OBJS) | $(BIN_DIR)
	ar rcs $@ $^

# 2. Compile the App (Link against Library)
$(APP_BIN): $(APP_SRC) $(TARGET_LIB)
	$(CC) $(CFLAGS) $(APP_SRC) -o $@ -L$(BIN_DIR) -ldsa

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf build

# Helper to run the app quickly
run: $(APP_BIN)
	./$(APP_BIN)

.PHONY: all clean run

-include $(OBJS:.o=.d)
