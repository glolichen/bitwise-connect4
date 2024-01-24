#include <stdlib.h>
#include <stdio.h>
#include "bitmask.h"

// enjoy tihs std::vector/java.util.ArrayList implimentation
ull *bitmasks, *vertical;
int bitmasks_size, vertical_size;

void add(ull **arr, int *size, ull add) {
	// increment the size, then reallocate the pointer, then set the last element
	*arr = (ull *) realloc(*arr, sizeof(ull) * (++(*size)));
	(*arr)[(*size) - 1] = add;
}

void init_bitmasks() {
	// initialize to 0
	bitmasks = (ull *) malloc(0);
	bitmasks_size = 0;
	vertical = (ull *) malloc(0);
	vertical_size = 0;

	// horizontal bitmasks
	for (int i = 0; i < 6; i++) {
		ull base = 15;
		for (int j = 0; j < 4; j++) {
			ull mask = base << j;
			add(&bitmasks, &bitmasks_size, mask << (i * 7));
		}
	}
	
	// vertical bitmasks
	for (int i = 0; i < 7; i++) {
		ull base = 2113665;
		for (int j = 0; j < 3; j++) {
			ull mask = base << (j * 7);
			add(&bitmasks, &bitmasks_size, mask << i);
		}
	}
	
	// left-down diagonal bitmasks
	for (int i = 0; i < 4; i++) {
		ull base = 16843009;
		for (int j = 0; j < 3; j++) {
			ull mask = base << i;
			add(&bitmasks, &bitmasks_size, mask << (j * 7));
		}
	}
	
	// right-down diagonal bitmasks
	for (int i = 3; i < 7; i++) {
		// this is technically not the right base but we shift it around so it's fine
		ull base = 266305;
		for (int j = 0; j < 3; j++) {
			ull mask = base << i;
			add(&bitmasks, &bitmasks_size, mask << (j * 7));
		}
	}

	// whole vertical column bitmasks for adding
	ull base = 34630287489;
	for (int i = 0; i < 7; i++)
		add(&vertical, &vertical_size, base << i);
}