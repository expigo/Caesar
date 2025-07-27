CC = gcc
EXECUTABLE = renderer

# Source dirs
SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
GRAPHICS_DIR = $(SRC_DIR)/graphics

# Find all C source files recursively
SOURCES = $(shell find $(SRC_DIR) -name '*.c')

# Compiler flags:
# -Wall: Enable all warnings
# -Wextra: Enable extra warnings
# $(shell ...): Run the command and substitute its output
CFLAGS = -Wall -Wextra -std=c99 -I$(SRC_DIR) $(shell pkg-config --cflags sdl3)

# Linker flags:
# Tell the linker to link against the SDL3 library
LDFLAGS = $(shell pkg-config --libs sdl3)

BUILD_DIR = build
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Default target: builds the executable
all: $(EXECUTABLE)

# Create build dirs
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/core
	mkdir -p $(BUILD_DIR)/graphics

# Rule to link the final executable
$(EXECUTABLE): $(BUILD_DIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# Compile sources files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the executable
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

# Show project struture
tree:
	tree src/ || find src/ -type f | sort

# Debug: show variables
debug:
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "CFLAGS: $(CFLAGS)"

.PHONY: all run clean tree debug
