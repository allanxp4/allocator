//alocador merda feito em 2 horas
//Allan Araujo
#include "alok.h"

MPool global_pool;

void* alok(int size) {
    if (size > global_pool.free) {
        int reallocSize = size + POOL_UPGRADE_EXTRA;
        global_pool.start_pointer = realloc(global_pool.start_pointer, reallocSize);
        global_pool.free += reallocSize;
        global_pool.pool_size += reallocSize;
    }
    Allocation a = firstFit(size);
    return a.pointer;
}

Allocation firstFit(int size) {
    for (int i = 0; i < global_pool.num_allocations; i++) {
        if (!global_pool.allocations[i].in_use) {
            if (global_pool.allocations[i].size >= size) {
                return global_pool.allocations[i];
            }
        }
    }
    return getNewAllocation(size);
}

Allocation getNewAllocation(int size){
    Allocation allocation;
    if(global_pool.is_initialized){
        allocation.pointer = global_pool.allocations[global_pool.num_allocations - 1].pointer + (global_pool.allocations[global_pool.num_allocations - 1].size);
    }
    else{
        allocation.pointer = global_pool.start_pointer;
    }
    allocation.in_use = true;
    allocation.size = size;
    global_pool.free -= size;
    global_pool.allocations[global_pool.num_allocations] = allocation;
    global_pool.num_allocations++;
    global_pool.is_initialized = true;
    return allocation;
};

Allocation bestFit(int size) {
    //TODO
}

void delok(void* pointer) {
    for (int i = 0; i < global_pool.num_allocations; i++) {
        if (global_pool.allocations[i].pointer == pointer) {
            global_pool.allocations[i].in_use = false;
            global_pool.free += global_pool.allocations[i].size;
        }
    }
}


void initAllocator() {
    void* basePointer = malloc(INITIAL_POOL_SIZE);
    global_pool.start_pointer = basePointer;
    global_pool.pool_size = INITIAL_POOL_SIZE;
    global_pool.free = INITIAL_POOL_SIZE;
}