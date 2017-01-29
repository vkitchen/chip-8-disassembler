/*
		MAIN.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdio.h>
#include <stdlib.h>
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

	struct string *s = file_slurp_c(file);
	printf("\"%s\" %d\n", s->str, s->bytes);
	string_append_c(s, "dog");
	printf("\"%s\" %d\n", s->str, s->bytes);
	return 0;
	}
