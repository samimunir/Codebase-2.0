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
    Physical memory variable.
*/
char *physical_mem;
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
    /*
        Allocate memory to simulate physical RAM.
    */
    physical_mem = malloc(MEMSIZE);
    if (physical_mem == NULL) {
        fprintf(stderr, "Failed to allocate physical memory.\n");
        exit(1);
    }
    /*
        Initialize the physical memory bitmap.
    */
    physical_mem_bitmap = malloc(BITMAP_SIZE(MEMSIZE));
    if (physical_mem_bitmap == NULL) {
        fprintf(stderr, "Failed to allocate physical memory bitmap.\n");
        exit(1);
    }
    /*
        Initialize all bits in the bitmap to 1 (assuming all pages
            are initially free).
    */
    memset(physical_mem_bitmap, 0xFF, BITMAP_SIZE(MEMSIZE));
    /*
        Initialize the virtual memory bitmap (assuming a one-level
            page table).
    */
    virtual_mem_bitmap = malloc(BITMAP_SIZE(MAX_MEMSIZE / PAGE_SIZE));
    if (virtual_mem_bitmap == NULL) {
        free(physical_mem);
        free(physical_mem_bitmap);
        fprintf(stderr, "Failed to allocate virtual memory bitmap.\n");
        exit(1);
    }
    memset(virtual_mem_bitmap, 0, BITMAP_SIZE(MAX_MEMSIZE / PAGE_SIZE));
}

void * translate(unsigned int vp){
    /*
        Extract virtual page number (VPN) and virtual page offset (VPO).
    */
    unsigned int vpn = vp / PAGE_SIZE;
    unsigned int vpo = vp % PAGE_SIZE;
    /*
        Check if the page directory entry is valid.
    */
    if (!page_directory.entries[vpn / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].valid) {
        /*
            Page directory entry is invalid.
        */
        fprintf(stderr, "Invalid virtual page number: %u.\n", vp);
        exit(1);
    }
    /*
        Get the pointer to the page table for this VPN.
    */
    PageTable *page_table = page_directory.entries[vpn / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table;
    /*
        Check if the page table entry is valid.
    */
    if (!page_table -> entries[vpn % (MAX_MEMSIZE / PAGE_SIZE)].valid) {
        /*
            Page table entry is invalid, handle page fault.
        */
        fprintf(stderr, "Page fault on virtual page; %u.\n", vp);
        // implement page fault handling here...
        return -1;
    }
    /*
        Extract physical page number (PPN) from the valid page entry.
    */
    unsigned int pfn = page_table -> entries[vpn % (MAX_MEMSIZE / PAGE_SIZE)].pfn;
    /*
        Combine PPN and VPO to get the physical address.
    */
    return (pfn + PAGE_SIZE) + vpo;
}

unsigned int find_free_frame() {
    /*
        Loop through the physical memory bitmap to find a free frame.
    */
    for (int i = 0; i < MEMSIZE / PAGE_SIZE; i++) {
        if (!test_bit(physical_mem_bitmap, i)) {
            /*
                Free frame found, set the bit in the bitmap and return
                    the frame number.
            */
            set_bit(physical_mem_bitmap, i);
            return i;
        }
    }
    /*
        No free frame found.
    */
    return -1;
}

unsigned int page_map(unsigned int vp){
    /*
        Extract virtual page number (VPN).
    */
    unsigned int vpn = vp / PAGE_SIZE;
    /*
        Check if the page table entry is valid.
    */
    if (page_directory.entries[vpn / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table -> entries[vpn % (MAX_MEMSIZE / PAGE_SIZE)].valid) {
        return page_directory.entries[vpn / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table -> entries[vpn % (MAX_MEMSIZE / PAGE_SIZE)].pfn;
    }
    /*
        Page table entry is not valid, need to allocate a physical page frame.
    */
    unsigned int free_frame = find_free_frame();
    if (free_frame == -1) {
        /*
            No free frame found, handle error.
        */
        fprintf(stderr, "No free physical memory available.\n");
        exit(1);
    }
    /*
        Update page table entry with the allocated frame number.
    */
    page_directory.entries[vpn / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table -> entries[vpn % (MAX_MEMSIZE / PAGE_SIZE)].valid = 1;
    page_directory.entries[vpn / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table -> entries[vpn % (MAX_MEMSIZE / PAGE_SIZE)].pfn = free_frame;
    /*
        Set the corresponding bit in the virtual memory bitmap to 1 (page is now mapped).
    */
    set_bit(virtual_mem_bitmap, vpn);
    /*
        Return the allocated physical page number.
    */
    return free_frame;
}

unsigned int find_free_virtual_pages(unsigned int num_pages) {
    /*
        Loop through the virtual memory bitmap to find a contiguous block of free pages. 
    */
    for (int i = 0; i < MAX_MEMSIZE / PAGE_SIZE; i++) {
        /*
            Check if there are enough consecutive free pages starting from this position.
        */
        if (test_bit(virtual_mem_bitmap, i)) {
            continue; // skip if current bit is not free.
        }
        int free_count = 1;
        for (int j = 1; j < num_pages; j++) {
            if (test_bit(virtual_mem_bitmap, i + j)) {
                break; // not enough consecutive free pages, restart search.
            }
            free_count++;
        }
        if (free_count == num_pages) {
            /*
                Contiguous block found, set bits in the bitmap and return starting VPN.
            */
            for (int j = 0; j < num_pages; j++) {
                set_bit(virtual_mem_bitmap, i + j);
            }
            return i;
        }
        /*
            Not enough contiguous free pages starting from this position, continue search.
        */
    }
    /*
        No contiguous block found.
    */
    return -1;
}

void * t_malloc(size_t n){
    /*
        Calculate the number of virtual pages required (round up).
    */
    unsigned int num_pages = (n + PAGE_SIZE - 1) / PAGE_SIZE;
    /*
        Find a contiguous block of free virtual pages.
    */
    unsigned int start_vpn = find_free_virtual_pages(num_pages);
    if (start_vpn == -1) {
        /*
            No enough contiguous free virtual pages, handle error (e.g., out of memory).
        */
        fprintf(stderr, "Not enough contiguous free virtual memory.\n");
        return NULL;
    }
    /*
        Calculate and return the starting virtual address for the allocated memory.
    */
    return (void*) (start_vpn * PAGE_SIZE);
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