/*
    Sami Munir
    April 11th, 2024
    Codebase 2.0
    Data Structures & Algorithms
    > static-array
    > C implementation
*/

#include "static-array.h"
#include "static-array.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    printf("\nstatic-array implementation in C\n");

    int* static_array = NULL;
    static_array = init_static_array(3);

    return EXIT_SUCCESS;
}