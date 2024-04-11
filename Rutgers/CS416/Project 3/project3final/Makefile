CC = gcc
CFLAGS = -g -Wall -m32 -c  # Compilation flags
AR = ar -rc                 # Command to create a static library
RANLIB = ranlib             # Command to index the static library
LDFLAGS = -m32 -pthread             # Linking flags, used for linking the test executable

# Object files needed by the library
OBJECTS = my_vm.o

# The library we're compiling
LIBRARY = libmy_vm.a

# Phony targets for clean and all
.PHONY: all clean test

# Default target builds the library and then the test executable
all: $(LIBRARY) test

# Rule to make the library
$(LIBRARY): $(OBJECTS)
	$(AR) $@ $^
	$(RANLIB) $@

# Rule to compile the test executable
test: test.o $(LIBRARY)
	$(CC) $(LDFLAGS) -o test test.o -L. -lmy_vm


%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# Clean rule for removing compiled files
clean:
	rm -rf *.o $(LIBRARY) test