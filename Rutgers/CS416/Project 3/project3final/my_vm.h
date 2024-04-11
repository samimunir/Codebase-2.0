#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/mman.h>
#include <stdint.h>

#define MAX_MEMSIZE (1ULL<<32)
#define MEMSIZE (1ULL<<30)
#define TLB_ENTRIES 256
#define PAGE_SIZE 8192



// Structures and global variables
typedef struct {
    // Physical memory simulation
    void *physical_mem;
    // Bitmaps for physical and virtual memory
    unsigned char *phys_bitmap;
    unsigned char *virt_bitmap;
    // Two-level page table directory
    void **page_directory;
     void **vp_to_pp_map; // Direct mapping from VP to physical address
    
} memory_manager_t;

typedef struct {
    unsigned int valid;  // Valid bit to indicate if the entry is in use
    unsigned int vpage;  // Virtual page number
    unsigned int ppage;  // Physical page number
} TLB_entry;


void initialize_memory_manager(void);
void set_bit(unsigned char *bitmap, int bit);
void clear_bit(unsigned char *bitmap, int bit);
int get_bit(unsigned char *bitmap, int bit);
unsigned int get_next_avail(unsigned char *bitmap, size_t size);


void set_physical_mem();

void * translate(unsigned int vp);

void* page_map(unsigned int vp);

void * t_malloc(size_t n);

int t_free(unsigned int vp, size_t n);

int put_value(unsigned int vp, void *val, size_t n);

int get_value(unsigned int vp, void *dst, size_t n);

void mat_mult(unsigned int a, unsigned int b, unsigned int c, size_t l, size_t m, size_t n);

void add_TLB(unsigned int vpage, unsigned int ppage);

int check_TLB(unsigned int vpage);

void print_TLB_missrate();
