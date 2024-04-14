/**
 * Main
*/

#include "heap.h"
#include "screen.h"
#include "scheduler.h"
#include "paging.h"
#include "ata.h"
#include "filesystem.h"

void print(char*);
void println();
void printi(int);

void kernel_main() {
	heap_init();
	paging_init();
	screen_init();
	process_init();
	scheduler_init();
	filesystem_init();
	print("troldefar kernel");
	println();
	print("protected mode");
	println();
	printi(42069);
	println();

	while(1);
}

void interrupt_handler(int interrupt_number) {
	println();
	print("Interrupt received");
	printi(interrupt_number);
}
