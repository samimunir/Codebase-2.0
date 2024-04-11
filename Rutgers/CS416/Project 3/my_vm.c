#include "my_vm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/mman.h>
#include <stdint.h>
#include <pthread.h>

//TODO: Define static variables and structs, include headers, etc.
#define OFFSET_BITS ((int)log2(PAGE_SIZE))
#define PT_INDEX_BITS ((32 - OFFSET_BITS) / 2)
#define PD_INDEX_BITS (32 - OFFSET_BITS - PT_INDEX_BITS)
#define INVALID_INDEX (unsigned int)-1
pthread_mutex_t mem_manager_mutex = PTHREAD_MUTEX_INITIALIZER;
TLB_entry TLB[TLB_ENTRIES];  // Array of TLB entries
unsigned long long TLB_hits = 0;
unsigned long long TLB_misses = 0;
size_t bitmap_size = MEMSIZE / PAGE_SIZE / 8;

memory_manager_t mem_manager;
void initialize_memory_manager(void);
unsigned int get_next_avail(unsigned char *bitmap, size_t size);




void set_bit(unsigned char *bitmap, int bit) {
    bitmap[bit / 8] |= 1 << (bit % 8);
}

void clear_bit(unsigned char *bitmap, int bit) {
    bitmap[bit / 8] &= ~(1 << (bit % 8));
}

int get_bit(unsigned char *bitmap, int bit) {
    return (bitmap[bit / 8] >> (bit % 8)) & 1;
}

unsigned int get_next_avail(unsigned char *bitmap, size_t size) {
   printf("Entering get_next_avail with size \n");
    // Print the bitmap's contents in binary for debugging
    
    for (size_t i = 0; i < size; i++) {
        for (int j = 7; j >= 0; j--) { // Print each bit in a byte
            //printf("%d", (bitmap[i] >> j) & 1);
        }
       // printf(" "); // Space between bytes for readability
    }
    //printf("\n");

    for (size_t i = 0; i < size; i++) {
        
        if (bitmap[i] != 0xFF) { // If not all bits are set
            for (int j = 0; j < 8; j++) { // Check each bit
                printf("Checking bit %zu in byte %zu\n", j, i);
                if (!(bitmap[i] & (1 << j))) {
                    
                    return i * 8 + j; // Return the bit index
                }
            }
        }
        printf("All bits set.\n");
    }

    printf("No available bit found. Exiting get_next_avail.\n");
    return INVALID_INDEX;
}

/*static*/ void initialize_memory_manager(void) {
    // Allocate and clear the physical memory bitmap
    printf("Initializing memory manager...\n");
    mem_manager.phys_bitmap = (unsigned char*)malloc(bitmap_size);
   
    memset(mem_manager.phys_bitmap, 0, bitmap_size);

    // Allocate and clear the virtual memory bitmap
    mem_manager.virt_bitmap = (unsigned char*)malloc(bitmap_size); // Same size for simplicity
    memset(mem_manager.virt_bitmap, 0, bitmap_size);
    if (mem_manager.virt_bitmap == NULL) {
    fprintf(stderr, "Failed to allocate virtual bitmap\n");
    exit(EXIT_FAILURE);
}

    // Initialize the page directory
    mem_manager.page_directory = (void**)malloc(sizeof(void*) * (1 << PD_INDEX_BITS));
    for (int i = 0; i < (1 << PD_INDEX_BITS); i++) {
        mem_manager.page_directory[i] = NULL; // Initially, no page tables are allocated
        

    }
   printf("Memory manager initialized successfully.\n");
}

void set_physical_mem(){
    initialize_memory_manager();
    
    mem_manager.physical_mem = malloc(MEMSIZE);
    if (!mem_manager.physical_mem) {
        perror("Failed to allocate physical memory");
        exit(1);
    }
}

void * translate(unsigned int vp){
    //TODO: Finish
  
     printf("translate: Translating virtual address 0x%x\n", vp);

    unsigned int pd_index = vp >> (PT_INDEX_BITS + OFFSET_BITS);
    unsigned int pt_index = (vp >> OFFSET_BITS) & ((1 << PT_INDEX_BITS) - 1);

    // Check TLB first
    int ppage = check_TLB(vp >> OFFSET_BITS);
    if (ppage != -1) { // TLB hit
        uintptr_t physical_address = (uintptr_t)mem_manager.physical_mem + (ppage * PAGE_SIZE);
        printf("translate: TLB hit, physical address: %p\n", (void*)physical_address);
        return (void*)physical_address;
    }

    // TLB miss, use page table
    if (!mem_manager.page_directory || !mem_manager.page_directory[pd_index]) {
        // Page directory entry not present for vp, create new mapping
        printf("translate: Page directory entry not present for vp 0x%x, creating new mapping.\n", vp);
        void* new_physical_page = page_map(vp);
        if (new_physical_page == NULL) {
            printf("translate: Failed to map virtual page 0x%x\n", vp);
            return NULL;
        }
        return new_physical_page;
    }

    void** pt = mem_manager.page_directory[pd_index];
    if (!pt || !pt[pt_index]) {
        // Page table entry not present for vp, this scenario should ideally not happen after page_map
        printf("translate: Page table entry not present for vp 0x%x even after mapping\n", vp);
        return NULL;
    }

    uintptr_t physical_page_base = (uintptr_t)pt[pt_index];
    void* physical_address = (void*)(physical_page_base);

    // Add mapping to TLB for future reference
    add_TLB(vp >> OFFSET_BITS, (physical_page_base - (uintptr_t)mem_manager.physical_mem) / PAGE_SIZE);

    printf("translate: TLB miss, physical address: %p\n", physical_address);
    return physical_address;
}



void *page_map(unsigned int vp) {
    // Ensure 'bitmap_size' is declared and calculated within this function's scope
     
    // set_physical_mem();

  //  pthread_mutex_lock(&mem_manager_mutex); // Ensure thread safety
  //  printf("inside of page_map after the lock \n");
    // Calculate page directory and table indices
 printf("page_map: Attempting to map virtual page 0x%x\n", vp);
  //  pthread_mutex_lock(&mem_manager_mutex);

    unsigned int pd_index = vp >> (PT_INDEX_BITS + OFFSET_BITS);
    unsigned int pt_index = (vp >> OFFSET_BITS) & ((1 << PT_INDEX_BITS) - 1);

    if (!mem_manager.page_directory) {
        mem_manager.page_directory = calloc(1 << PD_INDEX_BITS, sizeof(void*));
        if (!mem_manager.page_directory) {
            printf("Error: Failed to allocate memory for page directory.\n");
            pthread_mutex_unlock(&mem_manager_mutex);
            return NULL;
        }
    }

    if (!mem_manager.page_directory[pd_index]) {
        mem_manager.page_directory[pd_index] = calloc(1 << PT_INDEX_BITS, sizeof(void*));
        if (!mem_manager.page_directory[pd_index]) {
            printf("Error: Failed to allocate memory for page table.\n");
            pthread_mutex_unlock(&mem_manager_mutex);
            return NULL;
        }
    }

    void **pt = mem_manager.page_directory[pd_index];
    if (pt[pt_index]) {
        pthread_mutex_unlock(&mem_manager_mutex);
        return pt[pt_index]; // Page already mapped
    }

    unsigned int pp_index = get_next_avail(mem_manager.phys_bitmap, bitmap_size);
    if (pp_index == (unsigned int)-1) {
        printf("Error: No free physical pages available.\n");
        pthread_mutex_unlock(&mem_manager_mutex);
        return NULL;
    }

    uintptr_t physical_address = (uintptr_t)mem_manager.physical_mem + (pp_index * PAGE_SIZE);
    pt[pt_index] = (void*)physical_address;
    set_bit(mem_manager.phys_bitmap, pp_index);
    set_bit(mem_manager.virt_bitmap, vp / PAGE_SIZE);

    // Update TLB with new mapping
    add_TLB(vp >> OFFSET_BITS, pp_index); // Correct use of physical page index

   // pthread_mutex_unlock(&mem_manager_mutex);
    printf("page_map: Mapped virtual page 0x%x to new physical page: %p\n", vp, (void*)physical_address);

    return (void*)physical_address;
}
void *t_malloc(size_t n){
     printf("t_malloc: Requesting allocation of size %zu\n", n);
 //  pthread_mutex_lock(&mem_manager_mutex);
   // printf("in t_malloc after lock\n");
    size_t pages_needed = (n + PAGE_SIZE - 1) / PAGE_SIZE;
     printf("t_malloc: Pages needed for allocation: %zu\n", pages_needed);
    void *first_page_address = NULL; // To hold the address of the first allocated page

    for (size_t i = 0; i < pages_needed; ++i) {
        // Calculate bitmap_size within the function's scope if it's not a global variable
        printf("t_malloc: Iteration %zu of allocation loop\n", i + 1);
        
        size_t bitmap_size = MEMSIZE / PAGE_SIZE / 8;
        printf("t_malloc: Calculated bitmap size: %zu\n", bitmap_size);
        printf("t_malloc: About to call get_next_avail, virt_bitmap address: %p\n", mem_manager.virt_bitmap);
        unsigned int vp_index = get_next_avail(mem_manager.virt_bitmap, bitmap_size);
         printf("t_malloc: Virtual page index found: %u\n", vp_index);

        if (vp_index == (unsigned int)-1) {
            perror("Failed to find a free virtual page.");
            return NULL;
        }
        void * page_address = page_map(vp_index*PAGE_SIZE);
        if (i == 0) {
            first_page_address = page_address;
        } /*else {
            page_map(vp_index * PAGE_SIZE); // Mapping additional pages
        }*/
    }
    printf("out of the loop  of t_malloc \n");
  //  pthread_mutex_unlock(&mem_manager_mutex);
    printf("t_malloc: Allocation completed. First page address: %p\n", first_page_address);
    return first_page_address;
}
int t_free(unsigned int vp, size_t n){
    //TODO: Finish
   // pthread_mutex_lock(&mem_manager_mutex);

    unsigned int start_page = vp >> OFFSET_BITS;
    unsigned int end_page = (vp + n - 1) >> OFFSET_BITS;
    
    for (unsigned int p = start_page; p <= end_page; ++p) {
    clear_bit(mem_manager.phys_bitmap, p); 
    clear_bit(mem_manager.virt_bitmap, p);

    unsigned int pd_index = p >> PT_INDEX_BITS;
    unsigned int pt_index = p & ((1 << PT_INDEX_BITS) - 1);

    void** page_table = mem_manager.page_directory[pd_index];
    if (page_table != NULL) {
        // Clear the page table entry
        page_table[pt_index] = NULL;

        // Check if the page table is now empty
        int isEmpty = 1;
        for (int i = 0; i < (1 << PT_INDEX_BITS); i++) {
            if (page_table[i] != NULL) {
                isEmpty = 0;
                break;
            }
        }

        // Free the page table if it's empty and clear its entry in the page directory
        if (isEmpty) {
            free(page_table);
            mem_manager.page_directory[pd_index] = NULL;
        }
    }
}
   // pthread_mutex_unlock(&mem_manager_mutex);
    return 0; // Assuming 0 indicates success

}

int put_value(unsigned int vp, void *val, size_t n){
    //TODO: Finish
   printf("put_value: Starting, writing %zu bytes to virtual address 0x%x\n", n, vp);
    
  //  pthread_mutex_lock(&mem_manager_mutex);
    
    void * pp = translate(vp);
    if (!pp) {
        printf("put_value: Translation failed for virtual address 0x%x\n", vp);
        pthread_mutex_unlock(&mem_manager_mutex);
        return -1;
    }
    
    size_t bytes_in_first_page = PAGE_SIZE - (vp % PAGE_SIZE);
    size_t bytes_to_copy = n;
    
    while (bytes_to_copy > 0) {
        size_t bytes_to_transfer = (bytes_to_copy < bytes_in_first_page) ? bytes_to_copy : bytes_in_first_page;
        memcpy((void*)((uintptr_t)pp + (vp % PAGE_SIZE)), val, bytes_to_transfer);
        
        printf("put_value: Wrote %zu bytes to physical address %p (virtual address 0x%x)\n", bytes_to_transfer, pp, vp);
        
        vp += bytes_to_transfer;
        val = (char*)val + bytes_to_transfer; // Adjusting the pointer type for arithmetic operation
        bytes_to_copy -= bytes_to_transfer;
        
        if (bytes_to_copy > 0) {
            pp = translate(vp);
            if (!pp) {
                printf("put_value: Translation failed for virtual address 0x%x during continuation\n", vp);
                pthread_mutex_unlock(&mem_manager_mutex);
                return -1;
            }
            bytes_in_first_page = PAGE_SIZE;
        }
    }
    
   // pthread_mutex_unlock(&mem_manager_mutex);
    printf("put_value: Completed successfully\n");

    
    return 0;
}

int get_value(unsigned int vp, void *dst, size_t n){
    //TODO: Finish
   printf("get_value: Starting, reading %zu bytes from virtual address 0x%x\n", n, vp);
    
   // pthread_mutex_lock(&mem_manager_mutex);
    
    void *pp = translate(vp);
    if (!pp) {
        printf("get_value: Translation failed for virtual address 0x%x\n", vp);
        pthread_mutex_unlock(&mem_manager_mutex);
        return -1;
    }
    
    size_t bytes_in_first_page = PAGE_SIZE - (vp % PAGE_SIZE);
    size_t bytes_to_copy = n;
    
    while (bytes_to_copy > 0) {
        size_t bytes_to_transfer = (bytes_to_copy < bytes_in_first_page) ? bytes_to_copy : bytes_in_first_page;
        memcpy(dst, (void*)((uintptr_t)pp + (vp % PAGE_SIZE)), bytes_to_transfer);
        
        printf("get_value: Read %zu bytes from physical address %p (virtual address 0x%x)\n", bytes_to_transfer, pp, vp);
        
        vp += bytes_to_transfer;
        dst = (char*)dst + bytes_to_transfer; // Adjusting the pointer type for arithmetic operation
        bytes_to_copy -= bytes_to_transfer;
        
        if (bytes_to_copy > 0) {
            pp = translate(vp);
            if (!pp) {
                printf("get_value: Translation failed for virtual address 0x%x during continuation\n", vp);
                pthread_mutex_unlock(&mem_manager_mutex);
                return -1;
            }
            bytes_in_first_page = PAGE_SIZE;
        }
    }
    
   // pthread_mutex_unlock(&mem_manager_mutex);
    printf("get_value: Completed successfully\n");
    return 0;
}


void mat_mult(unsigned int a, unsigned int b, unsigned int c, size_t l, size_t m, size_t n){
    //TODO: Finish
     printf("mat_mult: Performing matrix multiplication\n");
   pthread_mutex_lock(&mem_manager_mutex);

    for (size_t i = 0; i < l; ++i) {
        for (size_t j = 0; j < n; ++j) {
            int sum = 0;
            for (size_t k = 0; k < m; ++k) {
                int val_a, val_b;
                get_value(a + ((i * m + k) * sizeof(int)), &val_a, sizeof(int));
                get_value(b + ((k * n + j) * sizeof(int)), &val_b, sizeof(int));
                sum += val_a * val_b;
            }
            put_value(c + ((i * n + j) * sizeof(int)), &sum, sizeof(int));
        }
    }

    pthread_mutex_unlock(&mem_manager_mutex);
     printf("mat_mult: Matrix multiplication completed.\n");
}

void initialize_TLB() {
    for (int i = 0; i < TLB_ENTRIES; ++i) {
        TLB[i].valid = 0;  // Mark all entries as invalid initially
    }
}

void add_TLB(unsigned int vpage, unsigned int ppage){
    //TODO: Finish
     printf("add_TLB: Adding mapping vpage 0x%x to ppage 0x%x\n", vpage, ppage);
    unsigned int index = vpage % TLB_ENTRIES;
    TLB[index].valid = 1;
    TLB[index].vpage = vpage;
    TLB[index].ppage = ppage;
    printf("add_TLB: Mapping added successfully.\n");
}

int check_TLB(unsigned int vpage){
    //TODO: Finish
    printf("check_TLB: Checking TLB for vpage 0x%x\n", vpage);
    int result = -1;
     unsigned int index = vpage % TLB_ENTRIES;
    if (TLB[index].valid && TLB[index].vpage == vpage) {
        TLB_hits++;
        return TLB[index].ppage;
        result = TLB[index].ppage;  // Return the physical page number
    } else {
        TLB_misses++;
        result = -1;  // Indicate TLB miss
    }
    printf("check_TLB: TLB %s for vpage 0x%x\n", (result != -1) ? "hit" : "miss", vpage);
    return result;
}

void print_TLB_missrate(){
    //TODO: Finish
    if (TLB_hits + TLB_misses == 0) {
        printf("No TLB accesses recorded.\n");
        return;
    }
    double missrate = (double)TLB_misses / (TLB_hits + TLB_misses);
    printf("TLB Miss Rate: %.2f%%\n", missrate * 100);
}