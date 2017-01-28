#
# CMAKELISTS.TXT
# --------------
#
# Copyright (c) 2017 Vaughan Kitchen
#
# Released under the MIT license (https://opensource.org/licenses/MIT)
#

project(CHIP8)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CONFIGURATION_TYPES Debug)

set(CHIP8_FILES
	source/memory.c
	)

add_library(CHIP8lib ${CHIP8_FILES})

# Find headers
include_directories(source)

add_executable(chip-8 source/main.c)
target_link_libraries(chip-8 CHIP8lib)
