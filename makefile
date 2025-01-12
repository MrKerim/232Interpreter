# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Iinclude -g

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN = program

# Source and Object Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default Target
all: $(OBJ_DIR) $(BIN)

# Create Object Directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Link Object Files into Executable
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the Program
run: all
	./$(BIN)

# Clean Up
clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all run clean
