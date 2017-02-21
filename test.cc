#define _CRT_SECURE_NO_WARNINGS
#include "dovzhyna.hh"
#include <stdio.h>
#include <string.h>
#include <assert.h>
long static inline fsize(FILE* f) {
	long old = ftell(f);
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, old, SEEK_SET);
	return size;
}
void static inline printhex(uint8_t* data, size_t sz) {
	for (int i = 0; i < sz; i++) {
		if (i) printf(" ");
		printf("%.2X", (unsigned)data[i]);
	}
}
int main(int argc, char **argv) {
	if (argc != 2) return -1;
	FILE* f = fopen(argv[1], "rb");
	if (!f) return -1;
	long filesize = fsize(f);
	char* text = new char[filesize+15];
	fread(text, filesize, 1, f);
	memset(text + filesize, 0xCC, 15);
	fclose(f);

	dovzhyna::OpState os;
	int lastop = 0;
	for (int i = 0; i < filesize+15;) {
		dovzhyna::decode(os, (uint8_t*)text + i, true);
		if (os.state == dovzhyna::S_ERROR) {
			printf("error %.8X\n", i);
			i++;
			continue;
		}
		if ((i & 15) == 0) {
			switch (lastop) {
			case 0xCC:
				printf("sub %.8X\n", i);
				break;
			case 0xE9:
			case 0xEA:
			case 0xC2:
			case 0xC3:
			case 0xFF:
				printf("maybe %.8X\n", i);
				break;
			}
			if(i==0) printf("maybe %.8X\n", i);
		}
		
		//printf("%.8X: ",i);
		//printhex(os.data, os.index);
		//printf("\n");
		assert(os.index);
		i += os.index;
		lastop = os.opcode;
	}
	
	delete[] text;
}