volatile unsigned char *video = 0xB000;

int nextTextPos = 0;
int currLine = 0;
int WHITE_COLOR = 15;
int TEXT_MODE_WIDTH = 80;

void print(char*);
void println();
void printi(int);

void kernel_main() {
	print("troldefar kernel");
	println();
	print("proc mode");
	println();
	printi(420);
	println();

	while(1);
}

void print(char *str) {
	int currCharLocationInVideoMem, currColorLocationInVidMem;

	while (*str != '\0') {
		currCharLocationInVidMem = nextTextPos * 2;
		currColorLocationInVidMem = currCharLocationInVidMem + 1;

		video[currCharLocationInVidMem] = *str;
		video[currColorLocationInVidMem] = WHITE_COLOR;

		nextTextPos++;

		str++;
	}	
}

void println() {
	nextTextPos = ++currLine * TEXT_MODE_WIDTH;
}

void printi(int number) {
	char* intToString[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8","9"};
	
	if (number >= 0 && number <= 9) {
		print(intToString[number]);
		return;
	}

	int remaining = number % 10;
	number = number / 10;

	printi(number);
	printi(remaining);
}
