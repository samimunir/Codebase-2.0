// #include "my_vm.h"

// //TODO: Define static variables and structs, include headers, etc.
// /*
//     Page frame structure
//     - this structure effectively tracks the allocated state and
//         optionally the reference count for shared pages, along
//         with a pointer to the data itself.
// */
// typedef struct page_frame {
//     /*
//         Flag indicating if the page is allocated (1) or free (0).
//     */
//     int allocated;
//     /*
//         Reference count for shared pages (optional).
//     */
//     int ref_count;
//     /*
//         Pointer to the actual data stored in the page frame.
//     */
//     void *data;
// } PageFrame;

// /*
//     Page table entry (PTE)
//     - this structure includes the valid bit and physical page number
//         for efficient virtual-to-physical address translation.
// */
// typedef struct pte {
//     /*
//         Valid bit indicating if the page table entry is valid (1) or invalid (0).
//     */
//     int valid;
//     /*
//         Physical page number this entry maps to.
//     */
//     unsigned int pfn;
//     /*
//         Additional fields can be added here if needed.
//         - permissions (read-only, write-only)
//     */
// } PTE;

// /*
//     Page table (one-level)
//     - assuming a page size of 4KB
//     - this structure defines a one-level page table using an array
//         of PTEs.
//         > can be modified to a multi-level structure if needed based
//             on address space requirements.
// */
// # define PAGE_SIZE 4096
// typedef struct page_table {
//     /*
//         Array of PTEs representing entries in the page table.
//     */
//     PTE entries[MAX_MEMSIZE / PAGE_SIZE];
// } PageTable;

// /*
//     Page directory entry (PDE)
//     - this structure defines a page directory entry with a pointer
//         to a child page table and a valid bit.
// */
// typedef struct pde {
//     /*
//         Pointer to a child page table (one-level)
//     */
//     PageTable *table;
//     /*
//         Valid bit indicating if the page directory entry is
//             valid (1) or invalid (0).
//     */
//     int valid;
//     /*
//         Additional fields can be added here if needed.
//     */
// } PDE;

// const int TLB_SIZE = 32;
// // TLB data structure (assuming a fixed-size TLB)
// static TLBEntry tlb[TLB_SIZE]; // Replace TLB_SIZE with your desired size
// static int tlb_index = 0; // Index for the next TLB entry
// unsigned int tlb_misses = 0;
// unsigned int total_translations = 0;

// /*
//     Top-level page directory.
//     - this structure defines the top-level page directory using an
//         array of PDEs.
// */
// // #define NUM_PT_ENTRIES (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))
// // #define NUM_PT_ENTRIES (MAX_MEMSIZE)
// #define NUM_PT_ENTRIES (PAGE_SIZE * sizeof(PageTable))
// typedef struct page_directory {
//     /*
//         Array of PDEs representing entries in the page directoy.
//     */
//     PDE entries[NUM_PT_ENTRIES];
// } PageDirectory;

// /*
//     Translation lookaside buffer (TLB) entry.
//     - this structure defines an entry of the TLB, storing the virtual
//         and physical page numbers for faster translation.
// */
// typedef struct tlb_entry {
//     /*
//         Virtual page number.
//     */
//     unsigned int vpn;
//     /*
//         Physical page number.
//     */
//     unsigned int pfn;
// } TLBEntry;

// /*
//     Two separate bitmaps to track free and allocated pages
//         efficiently.
//     - physical_mem_bitmap
//         > tracks free and allocated physical memory pages.
//     - virtual_mem_bitmap
//         > tracks free and allocated virtual memory pages
//             (page table entries).
// */
// /*
//     Size of bitmap in bytes.
// */
// #define BITMAP_SIZE(memsize) ((memsize) / 8)
// /*
//     Physical memory variable.
// */
// char *physical_mem;
// /*
//     Physical memory bitmap.
// */
// char *physical_mem_bitmap;
// /*
//     Virtual memory bitmap.
// */
// char *virtual_mem_bitmap;
// /*
//     Function to set a bit in the bitmap (1 indicates allocated).
// */
// void set_bit(char *bitmap, unsigned int bit_num) {
//     bitmap[bit_num / 8] |= (1 << (bit_num % 8));
// }

// /*
//     Function to clear a bit in the bitmap (0 indicates free).
// */
// void clear_bit(char *bitmap, unsigned int bit_num) {
//     bitmap[bit_num / 8] &= ~(1 << (bit_num % 8));
// }

// /*
//     Function to check if a bit is set (1) in the bitmap.
// */
// int test_bit(char *bitmap, unsigned int bit_num) {
//     return (bitmap[bit_num / 8] >> (bit_num % 8)) & 1;
// }

// void set_physical_mem(){
//     /*
//         Allocate memory to simulate physical RAM.
//     */
//     physical_mem = malloc(MEMSIZE);
//     if (physical_mem == NULL) {
//         fprintf(stderr, "Failed to allocate physical memory.\n");
//         exit(1);
//     }
//     /*
//         Initialize the physical memory bitmap.
//     */
//     physical_mem_bitmap = malloc(BITMAP_SIZE(MEMSIZE));
//     if (physical_mem_bitmap == NULL) {
//         fprintf(stderr, "Failed to allocate physical memory bitmap.\n");
//         exit(1);
//     }
//     /*
//         Initialize all bits in the bitmap to 1 (assuming all pages
//             are initially free).
//     */
//     memset(physical_mem_bitmap, 0xFF, BITMAP_SIZE(MEMSIZE));
//     /*
//         Initialize the virtual memory bitmap (assuming a one-level
//             page table).
//     */
//     virtual_mem_bitmap = malloc(BITMAP_SIZE(MAX_MEMSIZE / PAGE_SIZE));
//     if (virtual_mem_bitmap == NULL) {
//         free(physical_mem);
//         free(physical_mem_bitmap);
//         fprintf(stderr, "Failed to allocate virtual memory bitmap.\n");
//         exit(1);
//     }
//     memset(virtual_mem_bitmap, 0, BITMAP_SIZE(MAX_MEMSIZE / PAGE_SIZE));
// }

// void * translate(unsigned int vp){
//     /*
//         Extract virtual page number (VPN) and virtual page offset (VPO).
//     */
//     unsigned int vpn = vp / PAGE_SIZE;
//     unsigned int vpo = vp % PAGE_SIZE;
//     /*
//         Check if the page directory entry is valid.
//     */
//     if (!page_directory.entries[(vpn / (PAGE_SIZE * sizeof(PageTable))) % (MAX_MEMSIZE / PAGE_SIZE)].valid)
//     if (!page_directory.entries[vpn / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].valid) {
//         /*
//             Page directory entry is invalid.
//         */
//         fprintf(stderr, "Invalid virtual page number: %u.\n", vp);
//         exit(1);
//     }
//     /*
//         Get the pointer to the page table for this VPN.
//     */
//     PageTable *page_table = page_directory.entries[vpn / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table;
//     /*
//         Check if the page table entry is valid.
//     */
//     if (!page_table -> entries[vpn % (MAX_MEMSIZE / PAGE_SIZE)].valid) {
//         /*
//             Page table entry is invalid, handle page fault.
//         */
//         fprintf(stderr, "Page fault on virtual page; %u.\n", vp);
//         // implement page fault handling here...
//         return -1;
//     }
//     /*
//         Extract physical page number (PPN) from the valid page entry.
//     */
//     unsigned int pfn = page_table -> entries[vpn % (MAX_MEMSIZE / PAGE_SIZE)].pfn;
//     /*
//         Combine PPN and VPO to get the physical address.
//     */
//     return (pfn + PAGE_SIZE) + vpo;
// }

// unsigned int find_free_frame() {
//     /*
//         Loop through the physical memory bitmap to find a free frame.
//     */
//     for (int i = 0; i < MEMSIZE / PAGE_SIZE; i++) {
//         if (!test_bit(physical_mem_bitmap, i)) {
//             /*
//                 Free frame found, set the bit in the bitmap and return
//                     the frame number.
//             */
//             set_bit(physical_mem_bitmap, i);
//             return i;
//         }
//     }
//     /*
//         No free frame found.
//     */
//     return -1;
// }

// unsigned int page_map(unsigned int vp){
//     /*
//         Extract virtual page number (VPN).
//     */
//     unsigned int vpn = vp / PAGE_SIZE;
//     /*
//         Check if the page table entry is valid.
//     */
//     if (page_directory.entries[vpn / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table -> entries[vpn % (MAX_MEMSIZE / PAGE_SIZE)].valid) {
//         return page_directory.entries[vpn / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table -> entries[vpn % (MAX_MEMSIZE / PAGE_SIZE)].pfn;
//     }
//     /*
//         Page table entry is not valid, need to allocate a physical page frame.
//     */
//     unsigned int free_frame = find_free_frame();
//     if (free_frame == -1) {
//         /*
//             No free frame found, handle error.
//         */
//         fprintf(stderr, "No free physical memory available.\n");
//         exit(1);
//     }
//     /*
//         Update page table entry with the allocated frame number.
//     */
//     page_directory.entries[vpn / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table -> entries[vpn % (MAX_MEMSIZE / PAGE_SIZE)].valid = 1;
//     page_directory.entries[vpn / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table -> entries[vpn % (MAX_MEMSIZE / PAGE_SIZE)].pfn = free_frame;
//     /*
//         Set the corresponding bit in the virtual memory bitmap to 1 (page is now mapped).
//     */
//     set_bit(virtual_mem_bitmap, vpn);
//     /*
//         Return the allocated physical page number.
//     */
//     return free_frame;
// }

// unsigned int find_free_virtual_pages(unsigned int num_pages) {
//     /*
//         Loop through the virtual memory bitmap to find a contiguous block of free pages. 
//     */
//     for (int i = 0; i < MAX_MEMSIZE / PAGE_SIZE; i++) {
//         /*
//             Check if there are enough consecutive free pages starting from this position.
//         */
//         if (test_bit(virtual_mem_bitmap, i)) {
//             continue; // skip if current bit is not free.
//         }
//         int free_count = 1;
//         for (int j = 1; j < num_pages; j++) {
//             if (test_bit(virtual_mem_bitmap, i + j)) {
//                 break; // not enough consecutive free pages, restart search.
//             }
//             free_count++;
//         }
//         if (free_count == num_pages) {
//             /*
//                 Contiguous block found, set bits in the bitmap and return starting VPN.
//             */
//             for (int j = 0; j < num_pages; j++) {
//                 set_bit(virtual_mem_bitmap, i + j);
//             }
//             return i;
//         }
//         /*
//             Not enough contiguous free pages starting from this position, continue search.
//         */
//     }
//     /*
//         No contiguous block found.
//     */
//     return -1;
// }

// void * t_malloc(size_t n){
//     /*
//         Calculate the number of virtual pages required (round up).
//     */
//     unsigned int num_pages = (n + PAGE_SIZE - 1) / PAGE_SIZE;
//     /*
//         Find a contiguous block of free virtual pages.
//     */
//     unsigned int start_vpn = find_free_virtual_pages(num_pages);
//     if (start_vpn == -1) {
//         /*
//             No enough contiguous free virtual pages, handle error (e.g., out of memory).
//         */
//         fprintf(stderr, "Not enough contiguous free virtual memory.\n");
//         return NULL;
//     }
//     /*
//         Calculate and return the starting virtual address for the allocated memory.
//     */
//     return (void*) (start_vpn * PAGE_SIZE);
// }

// int t_free(unsigned int vp, size_t n){
//     /*
//         Check if the virtual page number (vp) is within the valid virtual memory range.
//     */
//     if (vp >= MAX_MEMSIZE / PAGE_SIZE) {
//         fprintf(stderr, "Invalid virtual page number for free.\n");
//         return;
//     }
//     /*
//         Loop through n virtual pages starting from vp.
//     */
//     for (int i = 0; i < n; i++) {
//         /*
//             Check if we reached the end of a valid allocation (invalid page table entry).
//         */
//         if (!page_directory.entries[vp + i / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table -> entries[i % (MAX_MEMSIZE / PAGE_SIZE)].valid) {
//             fprintf(stderr, "Trying to free unallocated memory.\n");
//             return; // trying to free memory that wasn't allocated.
//         }
//         /*
//             Free the physical frame assocaited with the virtual page.
//         */
//         unsigned int pfn = page_directory.entries[vp + i / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table->entries[i % (MAX_MEMSIZE / PAGE_SIZE)].pfn;
//         /*
//             Implement logic to free the physical frame (e.g., clear the corresponding bit in the physical memory bitmap).
//         */
//         /*
//             Invalidate the page table entry.
//         */
//         page_directory.entries[vp + i / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table -> entries[i % (MAX_MEMSIZE / PAGE_SIZE)].valid = 0;
//     }
//     /*
//         Clear the corresponding bits in the virtual memory bitmap for the free pages.
//     */
//     for (int i = vp; i < vp + n; i++) {
//         if (!test_bit(virtual_mem_bitmap, i)) {
//             break; // reached the end of the allocated block (already cleared bits).
//         }
//         clear_bit(virtual_mem_bitmap, i);
//     }
// }

// void handle_page_fault(unsigned int vp) {
//   // Find a free physical frame (implement logic to find a free pfn)
//   unsigned int pfn = allocate_physical_frame(); 
//   if (pfn == -1) {
//     // No free physical frame available, handle error (e.g., out-of-memory)
//     fprintf(stderr, "Failed to allocate physical frame for page fault\n");
//     return;
//   }

//   // Load the missing page from secondary storage (e.g., disk)
//   unsigned int offset = vp % (PAGE_SIZE / sizeof(unsigned char)); // Calculate offset within the page
//   // Implement logic to load the page data (size: PAGE_SIZE) from disk into the physical memory at 'pfn * PAGE_SIZE'
//   // ... (implementation details for loading page data from disk) ...

//   // Update the page table entry for the virtual page
//   page_directory.entries[vp / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table->entries[vp % (MAX_MEMSIZE / PAGE_SIZE)].pfn = pfn;
//   page_directory.entries[vp / (MAX_MEMSIZE / (PAGE_SIZE * sizeof(PageTable)))].table->entries[vp % (MAX_MEMSIZE / PAGE_SIZE)].valid = 1;
// }

// // Function to allocate a free physical frame (implementation omitted)
// unsigned int allocate_physical_frame() {
//   // Implement logic to search the physical memory bitmap and find a free physical frame
//   // You can use the test_bit function to check for free bits

//   // ... (implementation details for finding a free physical frame) ...

//   // If no free frame is found, return -1
//   // Loop through all physical frames (using MAX_MEMSIZE and PAGE_SIZE)
//   for (int i = 0; i < MAX_MEMSIZE / PAGE_SIZE; i++) {
//     // Check if the current frame is free using test_bit
//     if (!test_bit(physical_mem_bitmap, i)) {
//       // Set the corresponding bit in the bitmap to mark the frame as allocated
//       set_bit(physical_mem_bitmap, i);
//       return i; // Return the physical frame number (pfn)
//     }
//   }

//   // No free frame found
//   return -1;
// }

// int put_value(unsigned int vp, void *val, size_t n){
//     /*
//         Translate virtual page number (vp) to physical frame number (pfn).
//     */
//     unsigned int pfn = (unsigned int) translate(vp);
//     /*
//         Check for page faults (pfn == -1).
//     */
//     if (pfn == -1) {
//         // handle page fault (e.g., call handle_page_fault)
//         handle_page_fault(vp);
//         /*
//             Retry translation after handling the page fault.
//         */
//         pfn = (unsigned int) translate(vp);
//         if (pfn == -1) {
//             // page fault not resolved, handle error.
//             fprintf(stderr, "Failed to handle page fault for virtual page %u.\n", vp);
//             return 1;
//         }
//     }
//     // calculate physical address.
//     unsigned int physical_addr = pfn * PAGE_SIZE + (vp % (PAGE_SIZE / sizeof(unsigned int))) * sizeof(unsigned int);
//     // use a byte-based loop for flexibility with data types.
//     for (size_t i = 0; i < n; i++) {
//         *(unsigned char*) (physical_addr + i) = *(unsigned char*) (val + i);
//     }
//     return 0; // indicate success.
// }

// int get_value(unsigned int vp, void *dst, size_t n){
//     // Translate virtual page number (vp) to physical frame number (pfn)
//   unsigned int pfn = translate(vp);

//   // Check for page faults (pfn == -1)
//   if (pfn == -1) {
//     // Handle page fault (e.g., call handle_page_fault)
//     handle_page_fault(vp);
//     // Retry translation after handling the page fault
//     pfn = translate(vp);
//     if (pfn == -1) {
//       // Page fault not resolved, handle error (return a specific value?)
//       fprintf(stderr, "Failed to handle page fault for virtual page %u\n", vp);
//       // Consider returning a special value to indicate error (e.g., -1)
//       return -1;
//     }
//   }

//   // Calculate physical address
//   unsigned int physical_addr = pfn * PAGE_SIZE + (vp % (PAGE_SIZE / sizeof(unsigned int))) * sizeof(unsigned int);

//   // Read the value from the physical memory address
//   return *(unsigned int*)physical_addr;
// }

// void mat_mult(unsigned int a, unsigned int b, unsigned int c, size_t l, size_t m, size_t n){
//   // Argument validation (optional)
//   if (l != m || m != n) {
//     fprintf(stderr, "Error: Matrix dimensions incompatible for multiplication\n");
//     return;
//   }

//   // Loop through elements of the resulting matrix
//   for (size_t i = 0; i < l; i++) {
//     for (size_t j = 0; j < n; j++) {
//       int sum = 0;
//       // Loop through elements in a row of the resulting matrix
//       unsigned int result_addr;
//       for (size_t k = 0; k < m; k++) {
//         // Calculate virtual addresses
//         unsigned int addr1 = a + i * m * sizeof(int) + k * sizeof(int);
//         unsigned int addr2 = b + k * m * sizeof(int) + j * sizeof(int);
//         result_addr = c + i * n * sizeof(int) + j * sizeof(int);

//         // Access elements using get_value (passing additional arguments)
//         int element1 = get_value(addr1, &element1, sizeof(int)); // Address of element1 to store value
//         int element2 = get_value(addr2, &element2, sizeof(int)); // Address of element2 to store value
//         if (element1 == -1 || element2 == -1) { // Handle errors from get_value
//           fprintf(stderr, "Error: Page fault while reading matrices\n");
//           return;
//         }
//         sum += element1 * element2;
//       }
//       // Write the calculated value to the resulting matrix using put_value
//       put_value(result_addr, &sum, sizeof(int)); // Pass address of sum for writing
//     }
//   }
// }

// // Function to check if TLB is full
// bool tlb_isFull() {
//   // Check if the index is at the end of the TLB (or one before to avoid overwriting)
//   return (tlb_index == TLB_SIZE - 1);
// }

// // Function to evict an entry from TLB (LRU implementation)
// void evict_TLB_entry() {
//   // Since we don't have additional information about usage frequency,
//   // a simple FIFO (First-In-First-Out) eviction can be used here.
//   // You can implement LRU (Least Recently Used) for potentially better performance
//   // if you can track usage information.

//   // Move the index back by one (wrapping around if necessary)
//   tlb_index = (tlb_index == 0) ? TLB_SIZE - 1 : tlb_index - 1;
// }

// void add_TLB(unsigned int vpage, unsigned int ppage){
//     // Check if there's space available in the TLB
//   if (tlb_isFull()) {
//     // Implement TLB replacement policy (e.g., FIFO, LRU) to evict an entry
//     evict_TLB_entry();
//   }

//   // Add the new entry to the TLB data structure
//   tlb[tlb_index] = (TLBEntry){vpage, ppage};
//   tlb_index = (tlb_index + 1) % TLB_SIZE; // Update index for next entry
// }

// int check_TLB(unsigned int vpage){
//     // Loop through all TLB entries
//   for (int i = 0; i < TLB_SIZE; i++) {
//     // Check if the virtual page number in the TLB entry matches the provided vpn
//     if (tlb[i].vpn == vpage) {
//       return true; // TLB hit
//     }
//   }
//   return false; // TLB miss
// }

// void print_TLB_missrate(){
//     // Calculate miss rate (assuming total number of translations is tracked)
//   float miss_rate = (float)tlb_misses / total_translations;
//   printf("TLB miss rate: %.2f%%\n", miss_rate * 100.0f);
// }

/*
    TODO:
    - define static variables
    - define structs
    - include headers
    - etc.
*/

/*
    Required includes (libraries).
*/
#include "my_vm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

/*
    Required global variables.
*/
#define OFFSET_BITS ((int) log2 (PAGE_SIZE))

# define PT_INDEX_BITS ((32 - OFFSET_BITS) / 2)

# define PD_INDEX_BITS (32 - OFFSET_BITS - PT_INDEX_BITS)

/*
    Utility functions.
*/
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
    /*
        Loop through the bitmap to find an unset bit.
    */
    for (size_t i = 0; i < size * 8; i++) {
        if (!get_bit(bitmap, i)) {
            return i;
        }
    }
    /*
        Indicate failure if not free bit is found.
    */
    return -1;
}

static void initialize_memory_manager() {
    /*
        Allocate and clear the physical memory bitmap.
    */
    size_t bitmap_size = MEMSIZE / PAGE_SIZE / 8; // Number of bytes needed.
    mem_manager.phys_bitmap = (unsigned char*) malloc(bitmap_size);
    memset(mem_manager.phys_bitmap, 0, bitmap_size);
    /*
        Allocate and clear the virtual memory bitmap.
    */
    mem_manager.virt_bitmap = (unsigned char*) malloc(bitmap_size); // Same size for simplicity.
    memset(mem_manager.virt_bitmap, 0, bitmap_size);
    /*
        Initialize the page directory.
    */
    mem_manager.page_directory = (void**) malloc(sizeof(void*) * (1 << PD_INDEX_BITS));
    for (int i = 0; i < (1 << PD_INDEX_BITS); i++) {
        mem_manager.page_directory[i] = NULL; // Initially, no page tables are allocated.
    }
}

void set_physical_mem() {
    initialize_memory_manager();
    mem_manager.physical_mem = malloc(MEMSIZE);
    if (!mem_manager.physical_mem) {
        perror("Failed to allocate physical memory.");
        exit(1);
    }
}

void * translate(unsigned int vp) {
    unsigned int pd_index = vp >> (PT_INDEX_BITS + OFFSET_BITS);
    unsigned int pt_index = (vp >> OFFSET_BITS) & ((1 << PT_INDEX_BITS) - 1);
    unsigned int offset = vp & ((1 << OFFSET_BITS) - 1);

    void **pt = (void**) mem_manager.page_directory[pd_index];
    if (!pt) return NULL; // Page table not present.

    void *pp = pt[pt_index];
    if (!pp) return NULL; // Page not present.
    return (void*) ((uintptr_t) pp + offset);
}

unsigned int page_map(unsigned int vp) {
    /*
        Ensure bitmap_size is declared and calculated within this function's scope.
    */
    size_t bitmap_size = MEMSIZE / PAGE_SIZE / 8;
    
    unsigned int pd_index = vp >> (PT_INDEX_BITS + OFFSET_BITS);
    unsigned int pt_index = (vp >> OFFSET_BITS) & ((1 << PT_INDEX_BITS) - 1);

    if (!mem_manager.page_directory[pd_index]) {
        /*
            Allocate page table if not already present.
        */
        mem_manager.page_directory[pd_index] = malloc(sizeof(void*) * (1 << PT_INDEX_BITS));
        memset(mem_manager.page_directory[pd_index], 0, sizeof(void*) * (1 << PT_INDEX_BITS));
    }

    void **pt = (void**) mem_manager.page_directory[pd_index];

    if (!pt[pt_index]) {
        /*
            Map virtual page to physical page.
        */
        size_t bitmap_size = MEMSIZE / PAGE_SIZE / 8; // Re-declare bitmap_size if not globally defined.
        unsigned int pp_index = get_next_avail(mem_manager.phys_bitmap, bitmap_size);
        pt[pt_index] = (void*) ((uintptr_t) mem_manager.physical_mem + (pp_index * PAGE_SIZE));

        set_bit(mem_manager.phys_bitmap, pp_index);
        set_bit(mem_manager.virt_bitmap, vp / PAGE_SIZE);
    }
}

void * t_malloc(size_t n) {
    size_t pages_needed = (n + PAGE_SIZE - 1) / PAGE_SIZE;
    void *first_page_address = NULL; // To hold the address of the first allocated page.

    for (size_t i = 0; i < pages_needed; ++i) {
        /*
            Calculate bitmap_size within the function's scope if
                it is not declared as a global variable.
        */
        size_t bitmap_size = MEMSIZE / PAGE_SIZE / 8;
        unsigned int vp_index = get_next_avail(mem_manager.virt_bitmap, bitmap_size);
        if (vp_index == (unsigned int) -1) {
            perror("Failed to find a free virtual page.");
            return NULL;
        }
        if (i == 0) {
            first_page_address = page_map(vp_index * PAGE_SIZE);
        } else {
            page_map(vp_index * PAGE_SIZE); // Mapping additional pages.
        }
    }
    return first_page_address;
}

/*
    function t_free()
    - does not need to handle fragmentation (per project description)
*/
int t_free(unsigned int vp, size_t n) {
    /*
        Calculate the number of virtual pages to be freed.
    */
    size_t pages_to_free = (n + PAGE_SIZE - 1) / PAGE_SIZE;
    /*
        Iterate over each virtual page to be freed.
        1. calculate the virtual page index.
        2. translate the virtual page index to a physical page index.
    */
    for (size_t i = 0; i < pages_to_free; ++i) {
        unsigned int vp_index = vp + (i * PAGE_SIZE);
        void *pp = translate(vp_index);
        /*
            Return -1 for translation failure.
        */
        if (!pp) {
            return -1;
        }
        /*
            Invalidate the page table entry.
        */
        unsigned int pd_index = vp_index >> (PT_INDEX_BITS + OFFSET_BITS);
        unsigned int pt_index = (vp_index >> OFFSET_BITS) & ((1 << PT_INDEX_BITS) - 1);
        ((void**) mem_manager.page_directory[pd_index])[pt_index] = NULL;
        /*
            Clear the corresponding bit in the virtual memory bitmap.
        */
        set_bit(&mem_manager.virt_bitmap, vp_index / PAGE_SIZE);
        /*
            Mark the physical page as free in the physical memory bitmap.
        */
        unsigned int physical_page_index = ((uintptr_t) pp - (uintptr_t) mem_manager.physical_mem) / PAGE_SIZE;
        clear_bit(&mem_manager.phys_bitmap, physical_page_index);
    }
    /*
        Return 0 for success.
    */
    return 0;
}

int put_value(unsigned int vp, void *val, size_t n) {
    /*
        Error handling for invalid virtual address.
    */
    void *pp = translate(vp);
    if (!pp) {
        return -1;
    }

    /*
        Calculate the number of bytes within the first page.
    */
    size_t bytes_in_first_page = PAGE_SIZE - (vp % PAGE_SIZE);
    size_t bytes_to_copy = n;

    /*
        Handle data transfer across multiple pages (if applicable).
    */
    while (bytes_to_copy > 0) {
        size_t bytes_to_transfer = (bytes_to_copy < bytes_in_first_page) ? bytes_to_copy : bytes_in_first_page;
        memcpy((void*) ((uintptr_t) pp + (vp % PAGE_SIZE)), val, bytes_to_transfer);
        /*
            Update for next iteration (if more pages involved).
        */
        vp += bytes_to_transfer;
        val += bytes_to_transfer;
        bytes_to_copy -= bytes_to_transfer;
        /*
            Translate virtual address for next page (if applicable).
        */
        if (bytes_to_copy > 0) {
            pp = translate(vp);
            /*
                Handle error: trying to write beyond allocated memory.
            */
            if (!pp) {
                return -1;
            }
            bytes_in_first_page = PAGE_SIZE;
        }
    }
    /*
        Return 0 for success.
    */
    return 0;
}

int get_value(unsigned int vp, void *dst, size_t n) {
    /*
        TODO: finish
    */
}

void mat_multi(unsigned int a, unsigned int b, unsigned int c, size_t l, size_t m, size_t n) {
    /*
        TODO: finish
    */
}

void add_TLB(unsigned int vpage, unsigned int ppage) {
    /*
        TODO: finish
    */
}

int check_TLB(unsigned int vpage) {
    /*
        TODO: finish
    */
}

void print_TLB_missrate() {
    /*
        TODO: finish
    */
}