#include "my_vm.h"

//TODO: Define static variables and structs, include headers, etc.
/*
    Page frame structure
    - this structure effectively tracks the allocated state and
        optionally the reference count for shared pages, along
        with a pointer to the data itself.
*/
typedef struct page_frame {
    /*
        Flag indicating if the page is allocated (1) or free (0).
    */
    int allocated;
    /*
        Reference count for shared pages (optional).
    */
    int ref_count;
    /*
        Pointer to the actual data stored in the page frame.
    */
    void *data;
} PageFrame;

/*
    Page table entry (PTE)
    - this structure includes the valid bit and physical page number
        for efficient virtual-to-physical address translation.
*/
typedef struct pte {
    /*
        Valid bit indicating if the page table entry is valid (1) or invalid (0).
    */
    int valid;
    /*
        Physical page number this entry maps to.
    */
    unsigned int pfn;
    /*
        Additional fields can be added here if needed.
        - permissions (read-only, write-only)
    */
} PTE;

/*
    Page table (one-level)
    - assuming a page size of 4KB
    - this structure defines a one-level page table using an array
        of PTEs.
        > can be modified to a multi-level structure if needed based
            on address space requirements.
*/
# define PAGE_SIZE 4096
typedef struct page_table {
    /*
        Array of PTEs representing entries in the page table.
    */
    PTE entries[MAX_MEMSIZE / PAGE_SIZE];
} PageTable;

/*
    Page directory entry (PDE)
    - this structure defines a page directory entry with a pointer
        to a child page table and a valid bit.
*/
typedef struct pde {
    /*
        Pointer to a child page table (one-level)
    */
    PageTable *table;
    /*
        Valid bit indicating if the page directory entry is
            valid (1) or invalid (0).
    */
    int valid;
    /*
        Additional fields can be added here if needed.
    */
} PDE;

/*
    Top-level page directory.
    - this structure defines the top-level page directory using an
        array of PDEs.
*/
#define NUM_PT_ENTRIES (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))
typedef struct page_directory {
    /*
        Array of PDEs representing entries in the page directoy.
    */
    PDE entries[NUM_PT_ENTRIES];
} PageDirectory;

/*
    Translation lookaside buffer (TLB) entry.
    - this structure defines an entry of the TLB, storing the virtual
        and physical page numbers for faster translation.
*/
typedef struct tlb_entry {
    /*
        Virtual page number.
    */
    unsigned int vpn;
    /*
        Physical page number.
    */
    unsigned int pfn;
} TLBEntry;

/*
    Two separate bitmaps to track free and allocated pages
        efficiently.
    - physical_mem_bitmap
        > tracks free and allocated physical memory pages.
    - virtual_mem_bitmap
        > tracks free and allocated virtual memory pages
            (page table entries).
*/
/*
    Size of bitmap in bytes.
*/
#define BITMAP_SIZE(memsize) ((memsize) / 8)
/*
    Physical memory bitmap.
*/
char *physical_mem_bitmap;
/*
    Virtual memory bitmap.
*/
char *virtual_mem_bitmap;
/*
    Function to set a bit in the bitmap (1 indicates allocated).
*/
void set_bit(char *bitmap, unsigned int bit_num) {
    bitmap[bit_num / 8] |= (1 << (bit_num % 8));
}
/*
    Function to clear a bit in the bitmap (0 indicates free).
*/
void clear_bit(char *bitmap, unsigned int bit_num) {
    bitmap[bit_num / 8] &= ~(1 << (bit_num % 8));
}
/*
    Function to check if a bit is set (1) in the bitmap.
*/
int test_bit(char *bitmap, unsigned int bit_num) {
    return (bitmap[bit_num / 8] >> (bit_num % 8)) & 1;
}

void set_physical_mem(){
    //TODO: Finish
}

void * translate(unsigned int vp){
    //TODO: Finish
}

unsigned int page_map(unsigned int vp){
    //TODO: Finish
}

void * t_malloc(size_t n){
    //TODO: Finish
}

int t_free(unsigned int vp, size_t n){
    //TODO: Finish
}

int put_value(unsigned int vp, void *val, size_t n){
    //TODO: Finish
}

int get_value(unsigned int vp, void *dst, size_t n){
    //TODO: Finish
}

void mat_mult(unsigned int a, unsigned int b, unsigned int c, size_t l, size_t m, size_t n){
    //TODO: Finish
}

void add_TLB(unsigned int vpage, unsigned int ppage){
    //TODO: Finish
}

int check_TLB(unsigned int vpage){
    //TODO: Finish
}

void print_TLB_missrate(){
    //TODO: Finish
}