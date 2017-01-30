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
struct string *disassemble(struct string *code)
	{
	struct string *output = string_new();
	size_t pos = 0;

	for (pos = 0; pos < code->bytes; pos += 2)
		{
		printf("CODE: 0x%02hhx%02hhx\n", code->str[pos], code->str[pos+1]);
		if ((code->str[pos] & (15 << 4 | 15)) == 0 && (code->str[pos+1] & 15) == 0)
			{
			string_append_c(output, "CLS\n");
			}
		else if ((code->str[pos] & (15 << 4 | 15)) == 0)
			{
			string_append_c(output, "RET\n");
			}
		else if ((code->str[pos] & 15 << 4) == 0)
			{
			string_append_c(output, "SYS addr\n");
			}
		else if ((code->str[pos] & 15 << 4) == 1 << 4)
			{
			string_append_c(output, "JP addr\n");
			}
		else if ((code->str[pos] & 15 << 4) == 2 << 4)
			{
			string_append_c(output, "CALL addr\n");
			}
		else if ((code->str[pos] & 15 << 4) == 3 << 4)
			{
			string_append_c(output, "SE Vx, byte\n");
			}
		else if ((code->str[pos] & 15 << 4) == 4 << 4)
			{
			string_append_c(output, "SNE Vx, byte\n");
			}
		else if ((code->str[pos] & 15 << 4) == 5 << 4 && (code->str[pos+1] & 15) == 0)
			{
			string_append_c(output, "SE Vx, Vy\n");
			}
		else if ((code->str[pos] & 15 << 4) == 6 << 4)
			{
			string_append_c(output, "LD Vx, byte\n");
			}
		else if ((code->str[pos] & 15 << 4) == 7 << 4)
			{
			string_append_c(output, "ADD Vx, byte\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 0)
			{
			string_append_c(output, "LD Vx, Vy\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 1)
			{
			string_append_c(output, "OR Vx, Vy\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 2)
			{
			string_append_c(output, "AND Vx, Vy\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 3)
			{
			string_append_c(output, "XOR Vx, Vy\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 4)
			{
			string_append_c(output, "ADD Vx, Vy\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 5)
			{
			string_append_c(output, "SUB Vx, Vy\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 6)
			{
			string_append_c(output, "SHR Vx {, Vy}\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 7)
			{
			string_append_c(output, "SUBN Vx, Vy\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 14)
			{
			string_append_c(output, "SHL Vx {, Vy}\n");
			}
		else if ((code->str[pos] & 15 << 4) == 9 << 4 && (code->str[pos+1] & 15) == 0)
			{
			string_append_c(output, "SNE Vx, Vy\n");
			}
		else if ((code->str[pos] & 15 << 4) == 10 << 4)
			{
			string_append_c(output, "LD I, addr\n");
			}
		else if ((code->str[pos] & 15 << 4) == 11 << 4)
			{
			string_append_c(output, "JP V0, addr\n");
			}
		else if ((code->str[pos] & 15 << 4) == 12 << 4)
			{
			string_append_c(output, "RND Vx, byte\n");
			}
		else if ((code->str[pos] & 15 << 4) == 13 << 4)
			{
			string_append_c(output, "DRW Vx, Vy, nibble\n");
			}
		else if ((code->str[pos] & 15 << 4) == 14 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (9 << 4 | 14))
			{
			string_append_c(output, "SKP Vx\n");
			}
		else if ((code->str[pos] & 15 << 4) == 14 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (10 << 4 | 1))
			{
			string_append_c(output, "SKNP Vx\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == 7)
			{
			string_append_c(output, "LD Vx, DT\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == 10)
			{
			string_append_c(output, "LD Vx, K\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (1 << 4 | 5))
			{
			string_append_c(output, "LD DT, Vx\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (1 << 4 | 8))
			{
			string_append_c(output, "LD ST, Vx\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (1 << 4 | 14))
			{
			string_append_c(output, "ADD I, Vx\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (2 << 4 | 9))
			{
			string_append_c(output, "LD F, Vx\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (3 << 4 | 3))
			{
			string_append_c(output, "LD B, Vx\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (5 << 4 | 5))
			{
			string_append_c(output, "LD [I], Vx\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (6 << 4 | 5))
			{
			string_append_c(output, "LD Vx, [I]\n");
			}
		else
			{
			fprintf(stderr, "ERROR: disassemble() couldn't understand opcode 0x%02hhx%02hhx\n", code->str[pos], code->str[pos+1]);
			exit(1);
			}
		}

	return output;
	}
