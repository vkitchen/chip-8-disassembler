#include <stdio.h>
#include "file.h"
#include "string.h"

int main()
	{
	struct string *s = file_slurp_c("input.txt");
	printf("\"%s\" %d\n", s->str, s->bytes);
	return 0;
	}
