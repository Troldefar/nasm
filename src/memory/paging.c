#include "paging.h"

/**
 * Creation of entry
 * with corresponding bit flag setters
*/

int create_page_entry(
    int base_address, char present, char writable, char privilege_level, char cache_enabled, char write_through_cache, char accessed, char page_size, char dirty
) {
    int entry = 0;

    /**
     * bitwise OR
     * 1 = true
    */

    entry |= present;
    entry |= writable << 1;
    entry |= privilege_level << 2;
    entry |= write_through_cache << 3;
    entry |= cache_enabled << 4;
    entry |= accessed << 5;
    entry |= dirty << 6;
    entry |= page_size << 7;

    return base_address | entry;
}

void paging_init() {
    unsigned int curr_page_frame = 0;

    /**
     * Create page directories
     * Create page tables
    */

    page_directory = kalloc(PAGE_SIZE * AMOUNT_OF_PAGE_ENTRIES);

    for (int currPDE = 0; currPDE < PDE_NUM; currPDE++) {
        unsigned int *pagetable = kalloc(PAGE_SIZE * PTE_NUM);

        for (int currPTE = 0; currPTE < PTE_NUM; currPTE++, curr_page_frame++)
            pagetable[currPTE] = create_page_entry(curr_page_frame * 4096, 1, 0, 0, 1, 1, 0, 0, 0);

        page_directory[currPDE] = create_page_entry(pagetable, 1, 0, 0, 1, 1, 0, 0, 0);
    }

    load_page_directory();
    enable_paging();
}