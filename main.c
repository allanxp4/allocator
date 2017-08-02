#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <mem.h>
#include <sys/time.h>
#define INITIAL_POOL_SIZE 65536
#define POOL_UPGRADE_EXTRA 65536
#define INITIAL_ALLOCATION_SIZE 64
#define ALLOCATION_UPGRADE_SIZE 64


typedef struct allocation_str {
    void* pointer;
    int size;
    bool in_use;
} Allocation;

typedef struct memory_pool {
    void* start_pointer;
    int pool_size;
    int free;
    int num_allocations;
    bool is_initialized;
    Allocation allocations[];
} MPool;

void* alok(int size);
Allocation firstFit(int size);
Allocation bestFit(int size);
void delok(void* pointer);
void init();

Allocation getNewAllocation(int size);

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
        allocation.pointer = global_pool.allocations[global_pool.num_allocations - 1].pointer + (global_pool.allocations[global_pool.num_allocations - 1].size / 4);
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

int* batata;

long getMicrotime();

long getMicrotime() {
    return clock();
}

int main(){
    initAllocator();
    long startTime = getMicrotime();
    for(int i = 0; i < 1000; i++){
        batata = malloc(sizeof(int));
    }
    printf("malloc: %ld\n", getMicrotime() - startTime);
    startTime = getMicrotime();
    for(int i = 0; i < 1000; i++){
        batata = alok(sizeof(int));
    }
    printf("alok: %ld\n", getMicrotime() - startTime);
//    char* batata = (char *) alok(sizeof(char) + 70000);
//    char* batata2 = (char *) alok(sizeof(char) + 150000);
//    char* batata3 = (char *) alok(sizeof(char) + 38);
//    strcpy(batata, "oi");
//    strcpy(batata2, "entao");
//    strcpy(batata3, "mano");
//    printf("%s", batata);
//    printf("%s", batata2);
//    printf("%s", batata3);
    getchar();
    return 0;
}
