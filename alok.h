//
// Created by Allan on 02/08/2017.
//

#ifndef _ALOK_H
#define _ALOK_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <mem.h>

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

#endif _ALOK_H