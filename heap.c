#include "heap.h"

void heap_init() {
    heap_base = 0x100000;
}

/**
 * Grow the heap by N bytes
*/

int kalloc(int amountOfBytes) {
    unsigned int new_object_address = heap_base;

    heap_base += amountOfBytes;

    return new_object_address;
}

/**
 * Free memory by a given PID
*/

int freeMem(int pid) {

}