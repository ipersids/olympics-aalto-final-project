# Compiler and flags
CXX = g++
CC = gcc
CFLAGS += -c -std=c99 -g -Wall -Wextra -pedantic -Iinclude
LDFLAGS = -lm
EXECNAME = main

# Source and object files
C_FILES = $(wildcard src/*.c)
COBJECTS = $(C_FILES:src/%.c=src/%.o)

# OS-specific settings
ifeq ($(OS),Windows_NT)
    RM = del /f /q
    EXECUTABLE = $(EXECNAME).exe
else
    RM = rm -f
    EXECUTABLE = $(EXECNAME)
endif

.PHONY: all clean run

# Default target
all: $(EXECUTABLE)

# Linking executable
$(EXECUTABLE): $(COBJECTS)
	@echo "Linking for executable $(EXECUTABLE)"
	$(CC) $(COBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

# Compiling source files to object files
src/%.o: src/%.c
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -o $@ -c $<

# Cleaning up build artifacts
clean:
	@echo "Cleaning up"
	$(RM) src/*.o $(EXECUTABLE)

# Running the executable
run: $(EXECUTABLE)
	@echo "Running \"$(EXECUTABLE)\""
	@./$(EXECUTABLE)
