#include "static-array.h"
#include <stdio.h>
#include <stdlib.h>

struct static_array {
    int* array;
    int pointer;
    int size;
    int number_of_elements;
    int total_memory;
    int used_memory;
    int memory_available;
};

void print_static_array_stats(struct static_array* array) {
        printf("\tsize: %d\n", array -> size);
        printf("\tpointer: %d\n", array -> pointer);
        printf("\t> number_of_elements: %d\n", array -> number_of_elements);
        printf("\t> total_memory: %d bytes\n", array -> total_memory);
        printf("\t> memory_available: %d bytes\n", array -> memory_available);
        printf("\t> used_memory: %d bytes\n", array -> used_memory);
}

struct static_array * init_static_array(int size) {
    if (size <= 0) {
        printf("\ninit_static_array(%d) called...\n", size);
        printf("\t--<ERROR>-- cannot initialize static_array[] with size [%d].\n", size);
        return NULL;
    } else {
        struct static_array* array = (struct static_array*) malloc(sizeof(struct static_array));
        array -> array = (int*) malloc(size * sizeof(int));
        array -> pointer = -1;
        array -> size = size;
        array -> number_of_elements = 0;
        array -> total_memory = array -> size * sizeof(int);
        array -> memory_available = array -> total_memory;
        array -> used_memory = 0;
        printf("\ninit_static_array(%d) called...\n", size);
        printf("\tstatic_array[] initialized to size [%d].\n", size);
        print_static_array_stats(array);
        return array;
    }
}