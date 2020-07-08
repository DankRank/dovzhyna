#include <stdio.h>
#include <string.h>

/* format
 * 01aamiii
 * aa 1=prefix, 2=grp, 3=ud
 * m 1=modrm
 * iii 1=byte, 2=word, 3=three, 4=vord, 5=memory, 6=far
 */
int main()
{
	char line[512];
	int op = 0;
	int errors = 0;
	printf("static const char x86optab[512] =\n\"");
	while (fgets(line, 512, stdin)) {
		char *tok;
		char byte = 0;
		/* remove comments */
		tok = strchr(line, '#');
		if (tok)
			*tok = 0;

		if (tok = strtok(line, " \t\n\r")) {
			int byte;
			sscanf(tok, "%x", &byte);
			if (byte != op)
				fprintf(stderr, "Unexpected opcode number: '%s' != '%04X'\n", tok, op), errors|=1;
			byte = 64;
#define CHECK_ADD(kw, val, mask) \
			if (!strcmp(tok, kw)) { \
				if (byte & mask) \
					fprintf(stderr, "Conflicting token: '%s'\n", tok), errors|=1; \
				byte |= val; \
				continue; \
			}
			while ((tok = strtok(NULL, " \t\n\r"))) {
				CHECK_ADD("byte",    1,  7)
				CHECK_ADD("word",    2,  7)
				CHECK_ADD("three",   3,  7)
				CHECK_ADD("vord",    4,  7)
				CHECK_ADD("memory",  5,  7)
				CHECK_ADD("far",     6,  7)
				CHECK_ADD("modrm",   8,  8)
				CHECK_ADD("prefix", 16, 48)
				CHECK_ADD("ud",     32, 48)
				fprintf(stderr, "Unknown token: '%s'\n", tok), errors|=1;
			}
			if (byte == '\\') /* impossible combination (prefix+modrm+vord), but ok */
				putchar('\\');
			putchar(byte);
			if (++op == 0x100)
				op = 0x0F00;
			if (op == 0x1000)
				break;
			if ((op & 0x3F) == 0)
				printf("\"\n\"");
		}
	}
	if (op != 0x1000)
		fprintf(stderr, "Not enough entries\n"), errors|=1;
	printf("\";\n");
	return errors;
}
