/*
		STRING.H
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/
/*!
	@file
	@brief Define a String type more useful than cstrings and helpers around that type
	@author Vaughan Kitchen
	@copyright 2017 Vaughan Kitchen
*/

#ifndef STRING_H_
#define STRING_H_

struct string
	{
		size_t bytes;	//!< The length of the string in bytes not including the termininating null byte
		char *str;		//!< Pointer to the underlying array of chars
	};

/*
	STRING_FREE()
	-------------
*/
/*!
		@brief Frees a string object
		@param str [in] String to be freed
		@return Pointer to the allocated memory or NULL on error
*/
void string_free(struct string *str);

#endif
