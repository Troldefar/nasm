/**
 * troldefarkernels heap base address
*/

unsigned int heap_base;

void heap_init();
int freeMem(int pid);

/**
 * Declaration for troldefarkernels "malloc" function
*/

int kalloc(int);