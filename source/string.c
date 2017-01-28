/*
		STRING.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdlib.h>
#include "string.h"

/*
	STRING_FREE()
	-------------
*/
void string_free(struct string *str)
	{
	if (str->str != NULL)
		free(str->str);
	free(str);
	}
