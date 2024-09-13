# Makefile for synonym program

# Detect available C compiler
CC ?= gcc

# Compiler and flags
CFLAGS = -Wall -Wextra -std=c11

# Target executable
TARGET = synonym
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

# Source files
SRCS = synonym.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Rebuild everything
rebuild: clean all

# Install the executable to the specified directory
install: $(TARGET)
	install -m 755 $(TARGET) $(BINDIR)/$(TARGET)
	@echo "Installed $(TARGET) to $(BINDIR)/$(TARGET)"

# Uninstall the executable from the specified directory
uninstall:
	rm -f $(BINDIR)/$(TARGET)
	@echo "Uninstalled $(TARGET) from $(BINDIR)/$(TARGET)"

# Display help information
help:
	@echo "Makefile for synonym"
	@echo "Usage:"
	@echo "  make        - Build the synonym executable"
	@echo "  make clean  - Remove build files"
	@echo "  make rebuild- Clean and rebuild the executable"
	@echo "  make install- Install the executable to $(BINDIR)"
	@echo "  make uninstall- Uninstall the executable from $(BINDIR)"
	@echo "  make help   - Display this help information"

# Check for compiler options
check-compiler:
	@echo "Using compiler: $(CC)"
	@$(CC) --version || echo "Compiler not found or version check failed."

# Ensure a valid compiler is being used
.PHONY: check-compiler install uninstall help
