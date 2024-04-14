#include "screen.h"

int WHITE_COLOR = 15;
int TEXT_MODE_WIDTH = 80;

void screen_init() {
    video = 0xB8000;
    nextTextPos = 0;
    currLine = 0;
}

void print(char *str) {
	int currCharLocationInVideoMem, currColorLocationInVidMem;

	while (*str != '\0') {
		currCharLocationInVideoMem = nextTextPos * 2;
		currColorLocationInVidMem = currColorLocationInVidMem + 1;

		video[currCharLocationInVideoMem] = *str;
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