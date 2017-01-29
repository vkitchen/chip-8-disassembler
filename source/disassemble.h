/*
		DISASSEMBLE.H
		-------------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/
/*!
	@file
	@brief Disassembles the CHIP-8 bytecode
	@author Vaughan Kitchen
	@copyright 2017 Vaughan Kitchen
*/

#ifndef DISASSEMBLE_H_
#define DISASSEMBLE_H_

#include "string.h"

/*
	DISASSEMBLE()
	-------------
*/
/*!
	@brief Disassembles the CHIP-8 bytecode
	@param bytecode [in] The bytecode to disassemble
	@return A string of assembly
*/
struct string *disassemble(struct string *bytecode);

#endif
