/*
		FILE.H
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/
/*!
	@file
	@brief Utilities for dealing with file io
	@author Vaughan Kitchen
	@copyright 2017 Vaughan Kitchen
*/
#ifndef FILE_H_
#define FILE_H_

#include "string.h"

/*
	FILE_SLURP_C()
	------------
*/
/*!
		@brief Reads an entire file and returns it as a string
		@param filename [in] Filename to be read
		@return String containing the contents of the file
*/
struct string *file_slurp_c(char *filename);

#endif
