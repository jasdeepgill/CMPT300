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
    List_insertHead(&kallocator.free_blocks, List_createNode(kallocator.memory, _size)); 
    kallocator.available = _size;
    kallocator.used = 0;
}

void destroy_allocator() {
    free(kallocator.memory);
    struct nodeStruct* cur = kallocator.allocated_blocks;
    struct nodeStruct* cur2 = kallocator.free_blocks;
    struct nodeStruct* prev = NULL;
    struct nodeStruct* prev2 = NULL;
    while(cur != NULL)
    {
        prev = cur;
        cur = cur->next;
        List_deleteNode(&kallocator.allocated_blocks, prev);
        
    }
    while(cur2 != NULL)
    {   
        prev2 = cur2;
        cur2 = cur2->next;
        List_deleteNode(&kallocator.free_blocks, prev2);    
    }
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
            void* min_addr = kallocator.memory + kallocator.size + 1;
            struct nodeStruct* temp = NULL;
            while(cur_free != NULL)
            {
                if (cur_free->size >= _size && cur_free->block < min_addr)
                {
                    min_addr = cur_free->block;
                    temp = cur_free;
                }
                cur_free = cur_free->next;
            }
            if (temp != NULL)
            {
                ptr = temp->block;
                if (temp->size > _size)
                {
                    struct nodeStruct* remainder = List_createNode(temp->block + _size, temp->size - _size);
                    List_insertTail(&kallocator.free_blocks, remainder);
                }
                List_deleteNode(&kallocator.free_blocks, temp);
            }
            if (ptr == NULL)
            {
                // printf("Not enough memory.\n");
                break;
            }
            
            struct nodeStruct* block = List_createNode(ptr, _size);
            List_insertTail(&kallocator.allocated_blocks, block);
            kallocator.available -= _size;
            kallocator.used += _size;
            break;
        }
        case 1:
        {
            int min = kallocator.size+1;
            struct nodeStruct* temp = NULL;
            while(cur_free != NULL)
            {
                if (cur_free->size >= _size && cur_free->size < min)
                {
                    min = cur_free->size;
                    temp = cur_free;
                }
                cur_free = cur_free->next;
            }
            if (temp != NULL)
            {
                ptr = temp->block;
                if (temp->size > _size)
                {
                    struct nodeStruct* remainder = List_createNode(temp->block + _size, temp->size - _size);
                    List_insertTail(&kallocator.free_blocks, remainder);
                }
                List_deleteNode(&kallocator.free_blocks, temp);
            }
            if (ptr == NULL)
            {
                // printf("Not enough memory.\n");
                break;
            }
            struct nodeStruct* block = List_createNode(ptr, _size);
            List_insertTail(&kallocator.allocated_blocks, block);
            kallocator.available -= _size;
            kallocator.used += _size;
            break;
        }
        case 2:
        {
            int max = 0;
            struct nodeStruct* temp = NULL;
            while(cur_free != NULL)
            {
                if (cur_free->size >= _size && cur_free->size > max)
                {
                    max = cur_free->size;
                    temp = cur_free;
                }
                cur_free = cur_free->next;
            }
            if (temp != NULL)
            {
                ptr = temp->block;
                if (temp->size > _size)
                {
                    struct nodeStruct* remainder = List_createNode(temp->block + _size, temp->size - _size);
                    List_insertTail(&kallocator.free_blocks, remainder);
                }
                List_deleteNode(&kallocator.free_blocks, temp);
            }
            if (ptr == NULL)
            {
                // printf("Not enough memory.\n");
                break;
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
    struct nodeStruct* garbage[4] = {NULL};
    while(cur != NULL)
    {
        if ((cur->block + cur->size) == target->block && merged->block == NULL)
        {
            // printf("left = %p\n", cur->block);
            merged->block = cur->block;
            merged->size = cur->size + target->size;
            garbage[0] = cur;
        } else if ((cur->block + cur->size) == target->block && merged->block != NULL)
        {
            // printf("left = %p right = %p\n", cur->block, merged->block);
            merged->block = cur->block;
            merged->size += cur->size;
            garbage[1] = cur;
        }
        if ((target->block + target->size) == cur->block && merged->block == NULL)
        {
            // printf("right = %p\n", cur->block);
            merged->block = target->block;
            merged->size = target->size + cur->size;
            garbage[2] = cur;
        } else if ((target->block + target->size) == cur->block && merged->block != NULL){
            // printf("right = %p left = %p\n", cur->block, merged->block);
            merged->size += cur->size;
            garbage[3] = cur;
        }
        cur = cur->next;
    }

    for (int i = 0; i < 4; ++i)
    {
        if (garbage[i] != NULL)
        {
            List_deleteNode(&kallocator.free_blocks, garbage[i]);
        }
    }
    if (merged->block != NULL)
    {
        List_insertTail(&kallocator.free_blocks, merged);
        free(free_block);
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
    struct nodeStruct* cur1 = kallocator.free_blocks;
    while(cur1 != NULL)
    {
        printf("Block: %p Node size: %d\n", cur1->block, cur1->size);
        cur1 = cur1->next;
    }
    allocated_size = kallocator.used;
    allocated_chunks = List_countNodes(kallocator.allocated_blocks);
    free_size = kallocator.available;
    free_chunks = List_countNodes(kallocator.free_blocks);
    struct nodeStruct* cur = kallocator.free_blocks;
    if (kallocator.free_blocks == NULL)
    {
        smallest_free_chunk_size = 0;
    }
    while(cur != NULL)
    {
        if (cur->size < smallest_free_chunk_size)
        {
            smallest_free_chunk_size = cur->size;
        }
        if (cur->size > largest_free_chunk_size)
        {
            largest_free_chunk_size = cur->size;
        }
        cur = cur->next;
    }
    printf("Allocated size = %d\n", allocated_size);
    printf("Allocated chunks = %d\n", allocated_chunks);
    printf("Free size = %d\n", free_size);
    printf("Free chunks = %d\n", free_chunks);
    printf("Largest free chunk size = %d\n", largest_free_chunk_size);
    printf("Smallest free chunk size = %d\n", smallest_free_chunk_size);
}

// valgrind --leak-check=full --show-leak-kinds=all --num-callers=20 ./kallocation

