/*
		FILE.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file.h"
#include "memory.h"
#include "string.h"

/*
	FILE_SLURP_C()
	------------
*/
struct string *file_slurp_c(char *filename)
	{
	FILE *fh;
	struct stat details;
	size_t file_length = 0;
	struct string *result = memory_alloc(sizeof(*result));

	if ((fh = fopen(filename, "rb")) != NULL)
		{
		if (fstat(fileno(fh), &details) == 0)
			if ((file_length = details.st_size) != 0)
				{
				result->str = memory_alloc(sizeof(*result->str) * (file_length + 1));
				result->bytes = file_length;
				result->str[result->bytes] = '\0';
				if (fread(&result->str[0], details.st_size, 1, fh) != 1)
					{
					free(result->str);
					result->str = NULL;
					result->bytes = 0;
					}
				}
		fclose(fh);
		}

	return result;
	}
