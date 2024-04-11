#include "my_vm.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_set_and_clear_bit() {
    printf("Testing set_bit and clear_bit...\n");
    unsigned char bitmap = 0; // Start with all bits cleared

    set_bit(&bitmap, 1);
    assert(get_bit(&bitmap, 1) == 1);
    
    clear_bit(&bitmap, 1);
    assert(get_bit(&bitmap, 1) == 0);

    printf("set_bit and clear_bit passed.\n");
}

void test_page_mapping_and_translation() {
    printf("Testing page_map and translate...\n");
    set_physical_mem();

    unsigned int vp = 0x12345; // Example virtual address
    void* mapped_addr = page_map(vp);
    assert(mapped_addr != NULL);

    void* translated_addr = translate(vp);
    printf("Mapped address: %p, Translated address: %p\n", (void*)mapped_addr, (void*)translated_addr);
    assert(translated_addr == mapped_addr);
    

    

    printf("page_map and translate passed.\n");
}

void test_memory_allocation_and_free() {
    printf("Testing t_malloc and t_free...\n");
    set_physical_mem();

    size_t size = PAGE_SIZE; // Allocate one page
    void* addr = t_malloc(size);
    assert(addr != NULL);

    int free_result = t_free((unsigned int)addr, size);
    assert(free_result == 0);

    printf("t_malloc and t_free passed.\n");
}

void test_put_and_get_value() {
    printf("Testing put_value and get_value...\n");
    set_physical_mem();

    void* addr = t_malloc(PAGE_SIZE);
    char test_data[] = "Hello, VM!";
    put_value((unsigned int)addr, test_data, strlen(test_data) + 1);

    char buffer[50];
    get_value((unsigned int)addr, buffer, strlen(test_data) + 1);
    printf("test_data: %p, buffer: %p\n", (void*)test_data, (void*)buffer);
    assert(strcmp(test_data, buffer) == 0);

    printf("put_value and get_value passed.\n");
}

void test_mat_mult() {
    set_physical_mem();
    size_t l = 3, m = 3, n = 3; // dimensions of the matrices
    unsigned int mat1[l][m], mat2[m][n], answer[l][n];

    // Initialize mat1 and mat2 with some values
    for (size_t i = 0; i < l; ++i) {
        for (size_t j = 0; j < m; ++j) {
            mat1[i][j] = i + j;
            mat2[j][i] = i - j;
        }
    }

    // Perform matrix multiplication
    mat_mult((unsigned int)mat1, (unsigned int)mat2, (unsigned int)answer, l, m, n);

    // Print the resulting matrix
    printf("Resulting matrix:\n");
    for (size_t i = 0; i < l; ++i) {
        for (size_t j = 0; j < n; ++j) {
            printf("%d ", answer[i][j]);
        }
        printf("\n");
    }
}




    

int main() {
   test_set_and_clear_bit();
   
    
   test_page_mapping_and_translation();
    test_memory_allocation_and_free();
    test_put_and_get_value();
    test_mat_mult();

    return 0;
}
