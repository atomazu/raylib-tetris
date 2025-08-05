# ---- Configuration ----
CC = gcc
BUILD_DIR = build
TARGET = $(BUILD_DIR)/game
RAYLIB_SRC = ./external/raylib/src
SRC_DIR = src
OBJ_DIR = $(BUILD_DIR)/obj

# ---- Source Files ----
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# ---- Compiler and Linker Flags ----
CFLAGS = -I $(RAYLIB_SRC) -I $(SRC_DIR) -g -Wall
LDFLAGS = -L $(BUILD_DIR)
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon

# ---- Build Targets ----
all: $(TARGET)

$(TARGET): $(OBJECTS) $(BUILD_DIR)/libraylib.a
	@echo "Linking..."
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LIBS)

$(BUILD_DIR)/libraylib.a: | $(OBJ_DIR)
	@echo "Building raylib library..."
	$(MAKE) -C $(RAYLIB_SRC) PLATFORM=PLATFORM_DESKTOP GLFW_LINUX_ENABLE_WAYLAND=TRUE
	@mv $(RAYLIB_SRC)/libraylib.a $@
	@$(MAKE) -C $(RAYLIB_SRC) clean

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# ---- Directory Creation ----
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# ---- Utility Targets ----
clean:
	@echo "Cleaning up..."
	rm -rf ${BUILD_DIR}

.PHONY: all clean
