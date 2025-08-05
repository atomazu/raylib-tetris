# Compiler and Target
CC = gcc
BUILD_DIR = build
TARGET = $(BUILD_DIR)/game

RAYLIB_SRC = ./external/raylib/src
SRC_DIR = src
OBJ_DIR = $(BUILD_DIR)/obj

# Find all .c source files in the source directory
SOURCES := $(wildcard $(SRC_DIR)/*.c)

# Create a list of object files in the object directory, based on the source files
# e.g., src/main.c becomes obj/main.o
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Compiler Flags
# -I tells gcc where to find header files (.h)
CFLAGS = -I $(RAYLIB_SRC) -I $(SRC_DIR) -g -Wall

# Linker Flags
# -L tells the linker where to find library files (.a, .so)
# -l tells the linker which libraries to link
LDFLAGS = -L $(RAYLIB_SRC)
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# The 'all' target is the first one, making it the default when you run 'make'
all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LIBS)

# Pattern rule to compile .c files into .o files
# This rule tells make how to create a .o file in obj/ from a .c file in src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule to clean up the project (remove executable and object files)
clean:
	@echo "Cleaning up..."
	rm -rf ${BUILD_DIR}

# Tell make that `all` and `clean` are commands, not files
.PHONY: all clean
