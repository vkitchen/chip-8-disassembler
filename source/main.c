/*
		MAIN.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdio.h>
#include <stdlib.h>
#include "disassemble.h"
#include "file.h"
#include "string2.h"

const char *usage = "\
chip-8 [FILE]\n";

int main(int argc, char **argv)
	{
	char *file;

	if (argc != 2)
		{
		printf(usage);
		exit(0);
		}

	file = argv[1];
	if (!file_exists(file))
		{
		printf("ERROR: could not find file \"%s\"\n", file);
		exit(1);
		}

	struct string *code = file_slurp_c(file);
	struct string *result = disassemble(code);
	printf("%s\n", result->str);
	return 0;
	}
