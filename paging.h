/**
 * page directory entries
 * 
 * 3 for testing in a 4kb env
*/

#define PDE_NUM 3
#define AMOUNT_OF_PAGE_ENTRIES 1024
#define PAGE_SIZE 4

/**
 * page table entries, respectively
*/

#define PTE_NUM 1024

extern void load_page_directory();
extern void enable_paging();

unsigned int *page_directory;

void paging_init();
int create_page_entry( int, char, char, char, char, char, char, char, char);