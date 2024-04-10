#include "screen.h"
#include "process.h"

void print(char*);
void println();
void printi(int);

void kernel_main() {
	screen_init();
	process_init();
	print("troldefar kernel");
	println();
	print("proc mode");
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
