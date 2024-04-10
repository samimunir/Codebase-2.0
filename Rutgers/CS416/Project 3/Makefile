OBJS = my_vm.o test.o
SOURCE = my_vm.c test.c
HEADER = my_vm.h
OUT = my_vm
FLAGS = -g -c -Wall -m32 # Add -m32 here for 32-bit compilation
LFLAGS = -lpthread -m32 # Add -m32 here to ensure linking is done for 32-bit
CC = gcc

.PHONY: all clean run

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) -g $^-o$@$(LFLAGS)

%.o:%.c$(HEADER)
	$(CC) $(FLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)