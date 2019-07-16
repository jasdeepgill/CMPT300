#include <stdio.h>
#include "kallocator.h"

int main(int argc, char* argv[]) {
    // initialize_allocator(100, FIRST_FIT);
    initialize_allocator(100, BEST_FIT);
    // initialize_allocator(100, WORST_FIT);
    // printf("Using first fit algorithm on memory size 100\n");

    long* p[50] = {NULL};
    for(long i=0; i<12; ++i) {
        p[i] = kalloc(sizeof(long));
        if(p[i] == NULL) {
            printf("Allocation failed\n");
            continue;
        }
        *(p[i]) = i;
        printf("p[%ld] = %p ; *p[%ld] = %ld\n", i, p[i], i, *(p[i]));
    }
    // *(p[0]) = 300;
    // printf("p[%d] = %p ; *p[%d] = %d\n", 0, p[0], 0, *(p[0]));
    print_statistics();

    for(int i=0; i<10; ++i) {
        if(i%2 == 0)
            continue;

        printf("Freeing p[%d] = %p\n", i, p[i]);
        kfree(p[i]);
        p[i] = NULL;
    }

    print_statistics();

    char* c[50] = {NULL};
    for(int i=0; i<2; ++i) {
        c[i] = kalloc(sizeof(char));
        if(c[i] == NULL) {
            printf("Allocation failed\n");
            continue;
        }
        *(c[i]) = (char) i;
        printf("c[%d] = %p ; *c[%d] = %d\n", i, c[i], i, *(c[i]));
    }

    print_statistics();

    for(int i=0; i<10; ++i) {
        if(i%2 == 1)
            continue;

        printf("Freeing p[%d] = %p\n", i, p[i]);
        kfree(p[i]);
        p[i] = NULL;
    }

    print_statistics();
    
    short* s[50] = {NULL};
    for(int i=0; i<1; ++i) {
        s[i] = kalloc(sizeof(short));
        if(s[i] == NULL) {
            printf("Allocation failed\n");
            continue;
        }
        *(s[i]) = (short) i;
        printf("s[%d] = %p ; *s[%d] = %d\n", i, s[i], i, *(s[i]));
    }
    // *(p[0]) = 300;
    // printf("p[%d] = %p ; *p[%d] = %d\n", 0, p[0], 0, *(p[0]));
    // printf("available_memory = %d\n", available_memory());

    void* before[100] = {NULL};
    void* after[100] = {NULL};
    compact_allocation(before, after);

    print_statistics();

    // You can assume that the destroy_allocator will always be the 
    // last funciton call of main function to avoid memory leak 
    // before exit

    destroy_allocator();

    return 0;
}
