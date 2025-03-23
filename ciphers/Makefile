# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Target executable
TARGET = test

# Source files
SRCS = testing.c cipher.c

# Object files (generated from source files)
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = chiper.h

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .c files into .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (not actual files)
.PHONY: all clean
