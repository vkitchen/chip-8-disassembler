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
		printf("CODE: %d\n", code[pos]);
		if ((code[pos] & (15 << 12 | 15 << 8 | 15)) == 0)
			{
			string_append_c(output, "CLS\n");
			}
		else if ((code[pos] & (15 << 12 | 15 << 8)) == 0)
			{
			string_append_c(output, "RET\n");
			}
		else if ((code[pos] & 15 << 12) == 0)
			{
			string_append_c(output, "SYS addr\n");
			}
		else if ((code[pos] & 15 << 12) == 1 << 12)
			{
			string_append_c(output, "JP addr\n");
			}
		else if ((code[pos] & 15 << 12) == 2 << 12)
			{
			string_append_c(output, "CALL addr\n");
			}
		else if ((code[pos] & 15 << 12) == 3 << 12)
			{
			string_append_c(output, "SE Vx, byte\n");
			}
		else if ((code[pos] & 15 << 12) == 4 << 12)
			{
			string_append_c(output, "SNE Vx, byte\n");
			}
		else if ((code[pos] & (15 << 12 | 15)) == 5 << 12)
			{
			string_append_c(output, "SE Vx, Vy\n");
			}
		else if ((code[pos] & 15 << 12) == 6 << 12)
			{
			string_append_c(output, "LD Vx, byte\n");
			}
		else if ((code[pos] & 15 << 12) == 7 << 12)
			{
			string_append_c(output, "ADD Vx, byte\n");
			}
		else if ((code[pos] & (15 << 12 | 15)) == 8 << 12)
			{
			string_append_c(output, "LD Vx, Vy\n");
			}
		else if ((code[pos] & (15 << 12 | 15)) == (8 << 12 | 1))
			{
			string_append_c(output, "OR Vx, Vy\n");
			}
		else if ((code[pos] & (15 << 12 | 15)) == (8 << 12 | 2))
			{
			string_append_c(output, "AND Vx, Vy\n");
			}
		else if ((code[pos] & (15 << 12 | 15)) == (8 << 12 | 3))
			{
			string_append_c(output, "XOR Vx, Vy\n");
			}
		else if ((code[pos] & (15 << 12 | 15)) == (8 << 12 | 4))
			{
			string_append_c(output, "ADD Vx, Vy\n");
			}
		else if ((code[pos] & (15 << 12 | 15)) == (8 << 12 | 5))
			{
			string_append_c(output, "SUB Vx, Vy\n");
			}
		else if ((code[pos] & (15 << 12 | 15)) == (8 << 12 | 6))
			{
			string_append_c(output, "SHR Vx {, Vy}\n");
			}
		else if ((code[pos] & (15 << 12 | 15)) == (8 << 12 | 7))
			{
			string_append_c(output, "SUBN Vx, Vy\n");
			}
		else if ((code[pos] & (15 << 12 | 15)) == (8 << 12 | 14))
			{
			string_append_c(output, "SHL Vx {, Vy}\n");
			}
		else if ((code[pos] & (15 << 12 | 15)) == 9 << 12)
			{
			string_append_c(output, "SNE Vx, Vy\n");
			}
		else if ((code[pos] & 15 << 12) == 10 << 12)
			{
			string_append_c(output, "LD I, addr\n");
			}
		else if ((code[pos] & 15 << 12) == 11 << 12)
			{
			string_append_c(output, "JP V0, addr\n");
			}
		else if ((code[pos] & 15 << 12) == 12 << 12)
			{
			string_append_c(output, "RND Vx, byte\n");
			}
		else if ((code[pos] & 15 << 12) == 13 << 12)
			{
			string_append_c(output, "DRW Vx, Vy, nibble\n");
			}
		else if ((code[pos] & (15 << 12 | 15 << 4 | 15)) == (14 << 12 | 9 << 4 | 14))
			{
			string_append_c(output, "SKP Vx\n");
			}
		else if ((code[pos] & (15 << 12 | 15 << 4 | 15)) == (14 << 12 | 10 << 4 | 1))
			{
			string_append_c(output, "SKNP Vx\n");
			}
		else if ((code[pos] & (15 << 12 | 15 << 4 | 15)) == (15 << 12 | 7))
			{
			string_append_c(output, "LD Vx, DT\n");
			}
		else if ((code[pos] & (15 << 12 | 15 << 4 | 15)) == (15 << 12 | 10))
			{
			string_append_c(output, "LD Vx, K\n");
			}
		else if ((code[pos] & (15 << 12 | 15 << 4 | 15)) == (15 << 12 | 1 << 4 | 5))
			{
			string_append_c(output, "LD DT, Vx\n");
			}
		else if ((code[pos] & (15 << 12 | 15 << 4 | 15)) == (15 << 12 | 1 << 4 | 8))
			{
			string_append_c(output, "LD ST, Vx\n");
			}
		else if ((code[pos] & (15 << 12 | 15 << 4 | 15)) == (15 << 12 | 1 << 4 | 14))
			{
			string_append_c(output, "ADD I, Vx\n");
			}
		else if ((code[pos] & (15 << 12 | 15 << 4 | 15)) == (15 << 12 | 2 << 4 | 9))
			{
			string_append_c(output, "LD F, Vx\n");
			}
		else if ((code[pos] & (15 << 12 | 15 << 4 | 15)) == (15 << 12 | 3 << 4 | 3))
			{
			string_append_c(output, "LD B, Vx\n");
			}
		else if ((code[pos] & (15 << 12 | 15 << 4 | 15)) == (15 << 12 | 5 << 4 | 5))
			{
			string_append_c(output, "LD [I], Vx\n");
			}
		else if ((code[pos] & (15 << 12 | 15 << 4 | 15)) == (15 << 12 | 6 << 4 | 5))
			{
			string_append_c(output, "LD Vx, [I]\n");
			}
		else
			{
			fprintf(stderr, "ERROR: disassemble() couldn't understand opcode %d\n", code[pos]);
			exit(1);
			}
		}

	return output;
	}
