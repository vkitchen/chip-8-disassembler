/*
		DISASSEMBLE.C
		-------------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "string2.h"

/*
	DISASSEMBLE()
	-------------
*/
struct string *disassemble(struct string *bytecode)
	{
	struct string *output = string_new();
	uint16_t *code = (uint16_t *)bytecode->str;
	size_t len = bytecode->bytes / 2;
	size_t pos = 0;

	for (pos = 0; pos < len; pos++)
		{
		if ((code[pos] & 15 << 12) == 0)
			{
			string_append_c(output, "CLS RET SYS\n");
			}
		else if ((code[pos] & 15 << 12) == 1 << 12)
			{
			string_append_c(output, "JP\n");
			}
		else if ((code[pos] & 15 << 12) == 2 << 12)
			{
			string_append_c(output, "CALL\n");
			}
		else if ((code[pos] & 15 << 12) == 3 << 12)
			{
			string_append_c(output, "SE\n");
			}
		else if ((code[pos] & 15 << 12) == 4 << 12)
			{
			string_append_c(output, "SNE\n");
			}
		else if ((code[pos] & 15 << 12) == 5 << 12)
			{
			string_append_c(output, "SE\n");
			}
		else if ((code[pos] & 15 << 12) == 6 << 12)
			{
			string_append_c(output, "LD\n");
			}
		else if ((code[pos] & 15 << 12) == 7 << 12)
			{
			string_append_c(output, "ADD\n");
			}
		else if ((code[pos] & 15 << 12) == 8 << 12)
			{
			string_append_c(output, "LD OR AND XOR ADD SUB SHR SUBN SHL\n");
			}
		else if ((code[pos] & 15 << 12) == 9 << 12)
			{
			string_append_c(output, "SNE\n");
			}
		else if ((code[pos] & 15 << 12) == 10 << 12)
			{
			string_append_c(output, "LD\n");
			}
		else if ((code[pos] & 15 << 12) == 11 << 12)
			{
			string_append_c(output, "JP\n");
			}
		else if ((code[pos] & 15 << 12) == 12 << 12)
			{
			string_append_c(output, "RND\n");
			}
		else if ((code[pos] & 15 << 12) == 13 << 12)
			{
			string_append_c(output, "DRW\n");
			}
		else if ((code[pos] & 15 << 12) == 14 << 12)
			{
			string_append_c(output, "SKP SKNP\n");
			}
		else if ((code[pos] & 15 << 12) == 15 << 12)
			{
			string_append_c(output, "LD ADD\n");
			}
		else
			{
			fprintf(stderr, "ERROR: disassemble() couldn't understand opcode %d\n", code[pos]);
			exit(1);
			}
		}

	return output;
	}
