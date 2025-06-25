CC = gcc

# Name of the final executable
EXECUTABLE = renderer

# All C source files in the directory
SOURCES = src/*.c

# Compiler flags:
# -Wall: Enable all warnings
# -Wextra: Enable extra warnings
# $(shell ...): Run the command and substitute its output
CFLAGS = -Wall -Wextra $(shell pkg-config --cflags sdl3)

# Linker flags:
# Tell the linker to link against the SDL3 library
LDFLAGS = $(shell pkg-config --libs sdl3)

# Default target: builds the executable
all: $(EXECUTABLE)

# Rule to link the final executable
$(EXECUTABLE): $(SOURCES)
	$(CC) $(SOURCES) -o $(EXECUTABLE) $(CFLAGS) $(LDFLAGS)

run:
	./$(EXECUTABLE)
clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean
