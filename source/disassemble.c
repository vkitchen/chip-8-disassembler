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
	char buffer[256]; /* excessively large general purpose most wonderful string buffer */

	for (pos = 0; pos < code->bytes; pos += 2)
		{
		/* Debugging code. Prints all opcodes */
		/* printf("CODE: 0x%02hhX%02hhX\n", code->str[pos], code->str[pos+1]); */

		if ((code->str[pos] & (15 << 4 | 15)) == 0 && (code->str[pos+1] & (15 << 4 | 15)) == 14 << 4)
			{
			string_append_c(output, "CLS\n");
			}
		else if ((code->str[pos] & (15 << 4 | 15)) == 0 && (code->str[pos+1] & (15 << 4 | 15)) == (14 << 4 | 14))
			{
			string_append_c(output, "RET\n");
			}
		else if ((code->str[pos] & 15 << 4) == 0)
			{
			sprintf(&buffer[0], "0x%02hhX%02hhX", code->str[pos] & 15, code->str[pos+1]);
			string_append_c(output, "SYS ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 1 << 4)
			{
			sprintf(&buffer[0], "0x%02hhX%02hhX", code->str[pos] & 15, code->str[pos+1]);
			string_append_c(output, "JP ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 2 << 4)
			{
			sprintf(&buffer[0], "0x%02hhX%02hhX", code->str[pos] & 15, code->str[pos+1]);
			string_append_c(output, "CALL ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 3 << 4)
			{
			sprintf(&buffer[0], "v%01hhX %d", code->str[pos] & 15, code->str[pos+1]);
			string_append_c(output, "SE ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 4 << 4)
			{
			sprintf(&buffer[0], "v%01hhX %d", code->str[pos] & 15, code->str[pos+1]);
			string_append_c(output, "SNE ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		/* else if ((code->str[pos] & 15 << 4) == 5 << 4 && (code->str[pos+1] & 15) == 0) */ /* supposadly correct version */
		else if ((code->str[pos] & 15 << 4) == 5 << 4)
			{
			sprintf(&buffer[0], "v%01hhX v%01hhX", code->str[pos] & 15, code->str[pos+1] >> 4);
			string_append_c(output, "SE ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 6 << 4)
			{
			sprintf(&buffer[0], "v%01hhX %d", code->str[pos] & 15, code->str[pos+1]);
			string_append_c(output, "LD ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 7 << 4)
			{
			sprintf(&buffer[0], "v%01hhX %d", code->str[pos] & 15, code->str[pos+1]);
			string_append_c(output, "ADD ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 0)
			{
			sprintf(&buffer[0], "v%01hhX v%01hhX", code->str[pos] & 15, code->str[pos+1] >> 4 & 15);
			string_append_c(output, "LD ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 1)
			{
			sprintf(&buffer[0], "v%01hhX v%01hhX", code->str[pos] & 15, code->str[pos+1] >> 4 & 15);
			string_append_c(output, "OR ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 2)
			{
			sprintf(&buffer[0], "v%01hhX v%01hhX", code->str[pos] & 15, code->str[pos+1] >> 4 & 15);
			string_append_c(output, "AND ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 3)
			{
			sprintf(&buffer[0], "v%01hhX v%01hhX", code->str[pos] & 15, code->str[pos+1] >> 4 & 15);
			string_append_c(output, "XOR ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 4)
			{
			sprintf(&buffer[0], "v%01hhX v%01hhX", code->str[pos] & 15, code->str[pos+1] >> 4 & 15);
			string_append_c(output, "ADD ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 5)
			{
			sprintf(&buffer[0], "v%01hhX v%01hhX", code->str[pos] & 15, code->str[pos+1] >> 4 & 15);
			string_append_c(output, "SUB ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 6)
			{
			sprintf(&buffer[0], "v%01hhX v%01hhX", code->str[pos] & 15, code->str[pos+1] >> 4 & 15);
			string_append_c(output, "SHR ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 7)
			{
			sprintf(&buffer[0], "v%01hhX v%01hhX", code->str[pos] & 15, code->str[pos+1] >> 4 & 15);
			string_append_c(output, "SUBN ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 8 << 4 && (code->str[pos+1] & 15) == 14)
			{
			sprintf(&buffer[0], "v%01hhX v%01hhX", code->str[pos] & 15, code->str[pos+1] >> 4 & 15);
			string_append_c(output, "SHL ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 9 << 4 && (code->str[pos+1] & 15) == 0)
			{
			sprintf(&buffer[0], "v%01hhX v%01hhX", code->str[pos] & 15, code->str[pos+1] >> 4 & 15);
			string_append_c(output, "SNE ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 10 << 4)
			{
			sprintf(&buffer[0], "0x%02hhX%02hhX", code->str[pos] & 15, code->str[pos+1]);
			string_append_c(output, "LD I, ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 11 << 4)
			{
			sprintf(&buffer[0], "0x%02hhX%02hhX", code->str[pos] & 15, code->str[pos+1]);
			string_append_c(output, "JP V0, ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 12 << 4)
			{
			sprintf(&buffer[0], "v%01hhX %d", code->str[pos] & 15, code->str[pos+1]);
			string_append_c(output, "RND ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 13 << 4)
			{
			sprintf(&buffer[0], "v%01hhX v%01hhX %hhu", code->str[pos] & 15, code->str[pos+1] >> 4 & 15, code->str[pos+1] & 15);
			string_append_c(output, "DRW ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 14 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (9 << 4 | 14))
			{
			sprintf(&buffer[0], "v%01hhX", code->str[pos] & 15);
			string_append_c(output, "SKP ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 14 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (10 << 4 | 1))
			{
			sprintf(&buffer[0], "v%01hhX", code->str[pos] & 15);
			string_append_c(output, "SKPN ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == 7)
			{
			sprintf(&buffer[0], "v%01hhX", code->str[pos] & 15);
			string_append_c(output, "LD ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, ", DT\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == 10)
			{
			sprintf(&buffer[0], "v%01hhX", code->str[pos] & 15);
			string_append_c(output, "LD ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, ", K\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (1 << 4 | 5))
			{
			sprintf(&buffer[0], "v%01hhX", code->str[pos] & 15);
			string_append_c(output, "LD DT, ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (1 << 4 | 8))
			{
			sprintf(&buffer[0], "v%01hhX", code->str[pos] & 15);
			string_append_c(output, "LD ST, ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (1 << 4 | 14))
			{
			sprintf(&buffer[0], "v%01hhX", code->str[pos] & 15);
			string_append_c(output, "ADD I, ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (2 << 4 | 9))
			{
			sprintf(&buffer[0], "v%01hhX", code->str[pos] & 15);
			string_append_c(output, "LD F, ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (3 << 4 | 3))
			{
			sprintf(&buffer[0], "v%01hhX", code->str[pos] & 15);
			string_append_c(output, "LD B, ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (5 << 4 | 5))
			{
			sprintf(&buffer[0], "v%01hhX", code->str[pos] & 15);
			string_append_c(output, "LD [I] ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, "\n");
			}
		else if ((code->str[pos] & 15 << 4) == 15 << 4 && (code->str[pos+1] & (15 << 4 | 15)) == (6 << 4 | 5))
			{
			sprintf(&buffer[0], "v%01hhX", code->str[pos] & 15);
			string_append_c(output, "SKP ");
			string_append_c(output, &buffer[0]);
			string_append_c(output, ", [I]\n");
			}
		else
			{
			fprintf(stderr, "WARNING: disassemble() couldn't understand opcode 0x%02hhX%02hhX\n", code->str[pos], code->str[pos+1]);
			sprintf(&buffer[0], "0x%02hhX%02hhX\n", code->str[pos], code->str[pos+1]);
			string_append_c(output, &buffer[0]);
			}
		}

	return output;
	}
