#include "static-array.h"
#include <stdio.h>
#include <stdlib.h>

int* init_static_array(int size) {
    if (size <= 0) {
        printf("\ninit_static_array(%d) called...\n--<ERROR>-- invalid [size] input.\n", size);
        return NULL;
    } else {
        printf("\ninit_static_array(%d) called...\n", size);
        int* static_array_pointer = (int*) malloc(size * sizeof(int));
        if (static_array_pointer == NULL) {
            printf("\t--<ERROR>-- dynamic memory allocation failure.\n");
            return NULL;
        } else {
            printf("\tstatic_array[] successfully initialized.\n");
            printf("\tsize: %d\n", size);
            printf("\tmemory: %d bytes\n", (size * sizeof(int)));
            return static_array_pointer;
        }
    }
}

bool is_valid(int* static_array) {
    if (static_array == NULL) {
        return false;
    } else {
        return true;
    }
}