#include "my_vm.h"

//TODO: Define static variables and structs, include headers, etc.
/*
    Page frame structure
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
