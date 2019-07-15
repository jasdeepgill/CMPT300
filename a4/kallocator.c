#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "kallocator.h"
#include "list.h"

struct KAllocator {
    enum allocation_algorithm aalgorithm;
    int size;
    void* memory;
    // Some other data members you want, 
    // such as lists to record allocated/free memory
    struct nodeStruct* allocated_blocks;
    struct nodeStruct* free_blocks;
    int available;
    int used;
};

struct KAllocator kallocator;


void initialize_allocator(int _size, enum allocation_algorithm _aalgorithm) {
    assert(_size > 0);
    kallocator.aalgorithm = _aalgorithm;
    kallocator.size = _size;
    kallocator.memory = malloc((size_t)kallocator.size);
    // Add some other initialization
    kallocator.allocated_blocks = NULL;
    kallocator.free_blocks = NULL;
    kallocator.available = _size;
    kallocator.used = 0;
    // kallocator.memory = (void*) 10;
    printf("killme\n");
    // printf("swag: %d\n", *(int*)(kallocator.memory+101));
}

void destroy_allocator() {
    free(kallocator.memory);

    // free other dynamic allocated memory to avoid memory leak
}

void* kalloc(int _size) {
    void* ptr = NULL;

    // Allocate memory from kallocator.memory 
    // ptr = address of allocated memory
    struct nodeStruct* cur_free = kallocator.free_blocks;
    switch(kallocator.aalgorithm)
    {
        case 0:
        {
            while(cur_free != NULL)
            {
                if (cur_free->block < ptr && cur_free->size >= _size)
                {
                    ptr = cur_free->block;
                    List_deleteNode(&kallocator.free_blocks, cur_free);
                }
                cur_free = cur_free->next;
            }
            if (ptr == NULL)
            {
                if (kallocator.available >= _size)
                {
                    ptr = kallocator.memory + kallocator.used;
                }
                else
                {
                    printf("Not enough memory.\n");
                }
            }
            
            struct nodeStruct* block = List_createNode(ptr, _size);
            List_insertTail(&kallocator.allocated_blocks, block);
            kallocator.available -= _size;
            kallocator.used += _size;
            break;
        }
        case 1:
        {
            struct nodeStruct* min = kallocator.free_blocks;
            while(cur_free != NULL)
            {
                if (cur_free->size >= _size && cur_free->size < min->size)
                {
                    min = cur_free;
                }
                cur_free = cur_free->next;
            }
            if (min != NULL)
            {
                ptr = min->block;
                List_deleteNode(&kallocator.free_blocks, min);
            }
            if (ptr == NULL)
            {
                if (kallocator.available >= _size)
                {
                    ptr = kallocator.memory + kallocator.used;
                }
                else
                {
                    printf("Not enough memory.\n");
                }
            }
            struct nodeStruct* block = List_createNode(ptr, _size);
            List_insertTail(&kallocator.allocated_blocks, block);
            kallocator.available -= _size;
            kallocator.used += _size;
            break;
        }
        case 2:
        {
            struct nodeStruct* max = kallocator.free_blocks;
            while(cur_free != NULL)
            {
                if (cur_free->size >= _size && cur_free->size > max->size)
                {
                    max = cur_free;
                }
                cur_free = cur_free->next;
            }
            if (max != NULL)
            {
                ptr = max->block;
                List_deleteNode(&kallocator.free_blocks, max);
            }
            if (ptr == NULL)
            {
                if (kallocator.available >= _size)
                {
                    ptr = kallocator.memory + kallocator.used;
                }
                else
                {
                    printf("Not enough memory.\n");
                }
            }
            struct nodeStruct* block = List_createNode(ptr, _size);
            List_insertTail(&kallocator.allocated_blocks, block);
            kallocator.available -= _size;
            kallocator.used += _size;
            break;
        }
        default:
        printf("WTF\n");
        break;
    }
    return ptr;
}

void kfree(void* _ptr) {
    assert(_ptr != NULL);
    struct nodeStruct* target = List_findNode(kallocator.allocated_blocks, _ptr);
    struct nodeStruct* free_block = List_createNode(target->block, target->size);
    struct nodeStruct* cur = kallocator.free_blocks;
    struct nodeStruct* merged = List_createNode(NULL, 0);
    while(cur != NULL)
    {
        if ((cur->block + cur->size) == target->block)
        {
            merged->block = cur->block;
            merged->size = cur->size + target->size;
        }
        if ((target->block + target->size) == cur->block)
        {
            merged->block = target->block;
            merged->size = target->size + target->next->size;
        }
        cur = cur->next;
    }

    if (merged->block != NULL)
    {
        List_insertTail(&kallocator.free_blocks, merged);
    } else
    {
        List_insertTail(&kallocator.free_blocks, free_block);
        free(merged);
    }
    kallocator.available += target->size;
    kallocator.used -= target->size;
    List_deleteNode(&kallocator.allocated_blocks, target);
}

int compact_allocation(void** _before, void** _after) {
    int compacted_size = 0;

    // compact allocated memory
    // update _before, _after and compacted_size

    return compacted_size;
}

int available_memory() {
    int available_memory_size = 0;
    // Calculate available memory size
    available_memory_size = kallocator.available;
    return available_memory_size;
}

void print_statistics() {
    int allocated_size = 0;
    int allocated_chunks = 0;
    int free_size = 0;
    int free_chunks = 0;
    int smallest_free_chunk_size = kallocator.size;
    int largest_free_chunk_size = 0;

    // Calculate the statistics

    printf("Allocated size = %d\n", allocated_size);
    printf("Allocated chunks = %d\n", allocated_chunks);
    printf("Free size = %d\n", free_size);
    printf("Free chunks = %d\n", free_chunks);
    printf("Largest free chunk size = %d\n", largest_free_chunk_size);
    printf("Smallest free chunk size = %d\n", smallest_free_chunk_size);
}



