/*
    Required includes (libraries).
*/
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

/*
    Required definitions.
*/
#define MAX_MEMSIZE (1UL << 32)
#define MEMSIZE (1UL << 30)
#define TLB_ENTRIES 256
#define PAGE_SIZE 8192

/*
    Required structure & global variable definitions.
*/
typedef struct {
    /*
        Physical memory simulation.
    */
    void *physical_mem;
    /*
        Bitmaps for physical and virtual memory.
    */
    unsigned char phys_bitmap;
    unsigned char virt_bitmap;
    /*
        Two-level page table directory.
    */
    void **page_directory;
} memory_manager_t;

/*
    Utility function prototypes.
*/
static void initialize_memory_manager();

static unsigned int get_next_avail(unsigned char bitmap, size_t size);

/*
    Necessary function prototypes.
*/
void set_physical_mem();

void * translate(unsigned int vp);

unsigned int page_map(unsigned int vp);

void * t_malloc(size_t n);

int t_free(unsigned int vp, size_t n);

int put_value(unsigned int vp, void *val, size_t n);

int get_value(unsigned int vp, void *dst, size_t n);

void mat_mult(unsigned int a, unsigned int b, unsigned int c, size_t l, size_t m, size_t n);

void add_TLB(unsigned int vpage, unsigned int ppage);

int check_TLB(unsigned int vpage);

void print_TLB_missrate();