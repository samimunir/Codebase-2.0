#include "my_vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    /*
        Testing function set_physical_mem()
    */
    printf("Testing set_physical_mem()\n");
    set_physical_mem();
    printf("Physical memory initialized successfully!\n");

    /*
        Testing function translate()
    */
    printf("\nTesting translate()\n");
    unsigned int virtual_address = 0x1000;
    void *physical_address = translate(virtual_address);
    if (physical_address != NULL) {
        printf("Translated virtual address 0x%x to physical address: %p\n", virtual_address, physical_address);
    } else {
        printf("Translation failed for virtual address 0x%x\n", virtual_address);
    }

    /*
        Testing function page_map()
    */
    printf("\nTesting page_map()\n");
    unsigned int vp_to_map = 0x2000;
    void *mapped_page = page_map(vp_to_map);
    if (mapped_page != NULL) {
        printf("Mapped virtual page 0x%x to physical page: %p\n", vp_to_map, mapped_page);
    } else {
        printf("Failed to map virtual page 0x%x\n", vp_to_map);
    }

    /*
        Testing functions t_malloc() and t_free()
    */
    printf("\nTesting functions t_malloc() and t_free()\n");
    size_t size_to_allocate = 4096; // 1 page
    void *allocated_memory = t_malloc(size_to_allocate);
    if (allocated_memory != NULL) {
        printf("Allocated memory of size %zu bytes at address: %p\n", size_to_allocate, allocated_memory);
        // Free the allocated memory
        t_free((unsigned int)allocated_memory, size_to_allocate);
        printf("Freed memory allocated at address: %p\n", allocated_memory);
    } else {
        printf("Failed to allocate memory\n");
    }

    /*
        Testing functions put_value() & get_value()
    */
    printf("\nTesting functions put_value() & get_value()\n");
    unsigned int virtual_address2 = 0x3000;
    int value_to_put = 42;
    put_value(virtual_address2, &value_to_put, sizeof(int));
    int retrieved_value;
    get_value(virtual_address2, &retrieved_value, sizeof(int));
    printf("Value retrieved from virtual address 0x%x: %d\n", virtual_address2, retrieved_value);

    /*
    // Test mat_mult()
    printf("\nTesting mat_mult()\n");
    unsigned int matrix_a = 0x4000;
    unsigned int matrix_b = 0x5000;
    unsigned int matrix_c = 0x6000;
    size_t rows = 3;
    size_t cols = 3;
    mat_mult(matrix_a, matrix_b, matrix_c, rows, cols, cols);
    printf("Matrix multiplication performed successfully\n");

    // Test add_TLB() and check_TLB()
    printf("\nTesting add_TLB() and check_TLB()\n");
    unsigned int virtual_page = 0x7000;
    unsigned int physical_page = 0x8000;
    add_TLB(virtual_page, physical_page);
    int result = check_TLB(virtual_page);
    if (result != -1) {
        printf("TLB hit: Virtual page 0x%x maps to physical page: 0x%x\n", virtual_page, result);
    } else {
        printf("TLB miss for virtual page 0x%x\n", virtual_page);
    }

    // Test print_TLB_missrate()
    printf("\nTesting print_TLB_missrate()\n");
    print_TLB_missrate();
    */

    return EXIT_SUCCESS;
}