#ifndef HDATA_H
#define HDATA_H

/*
Copyright 2017 Andrew Burnett

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdint.h>

using namespace std;

struct block_pointer {
	uint32_t block_count;
	uint32_t pointer;
	char editorData[4]; //only used internally by Guerilla.
} __attribute__ ((packed)) ;

struct ident {
	uint16_t id;
	uint16_t tag_number;
} __attribute__ ((packed)) ;

struct dependency {
	uint32_t tag_group; //Or 'first class'
	uint32_t name_pointer; //Memory pointer to tag name/file path
	char reference_path_length[4]; //only used internally by Guerilla.
	ident id;
} __attribute__ ((packed)) ;

struct bound {
	float from;
	float to;
} __attribute__ ((packed)) ;

struct vertex {
	float x;
	float y;
	float z;
} __attribute__ ((packed)) ;

struct radian_rotation {
	float y;
	float p;
	float r;
} __attribute__ ((packed)) ;

struct colorbyte
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} __attribute__ ((packed)) ;

struct colorrgb
{
	float r;
	float g;
	float b;
} __attribute__ ((packed)) ;

struct colorargb
{
	float r;
	float g;
	float b;
	float a;
} __attribute__ ((packed)) ;

#endif
