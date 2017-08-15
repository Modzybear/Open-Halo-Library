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

// These constants are the fixed memory addresses Halo
// uses to load map files. The asset buffer, starting at
// the 'index' of tags, is dumped wholly into memory
// at these points in the respective versions.
const uint32_t RETAIL_MEMORY_ADDRESS = 0x40440000;
const uint32_t DEMO_MEMORY_ADDRESS = 0x4BF10000;
const uint32_t HEADER_LENGTH = 0x800;

/* General use Halo-specfic structures */

// A pointer in memory with count data proceeding it.
struct block_pointer {
	uint32_t block_count;
	uint32_t pointer;
	char editorData[4]; //only used internally by Guerilla.
} __attribute__ ((packed)) ;

// Unique numerated identities used for id a specific tag.
struct ident {
	uint16_t id;
	uint16_t tag_number;
} __attribute__ ((packed)) ;

// A reference to another tag that the referencing tag
// is likely dependent on.
struct dependency {
	uint32_t tag_group; //Or 'first class'
	uint32_t name_pointer; //Memory pointer to tag name/file path
	char reference_path_length[4]; //only used internally by Guerilla.
	ident id;
} __attribute__ ((packed)) ;

/* Halo Cache file structures */

// Retail header structure
struct header
{
	uint32_t head;		//'daeh'
	uint32_t build_version;	//5 = Xbox, 6 = demo, 7 = retail, 609 = CE
	uint32_t file_size;		//Total length of original file
	char padding[4];
	uint32_t tag_array;		//The offset to the tag array header, within the file
	uint32_t cache_length;	//Start of the tag array to the end of the map; original memory dump
	char padding1[8];
	char map_name[0x20];		//internal map name
	char build_date[0x20];	//The date tool built the cache file
	uint32_t map_type;		//0 = singleplayer, 1 = multiplayer, 2 = UI
	uint32_t crc32;		//checksum
	char padding2[0x794];
	uint32_t foot;		//'toof' in ascii
} __attribute__ ((packed));

// Tag index header structure
struct index_header
{
	uint32_t element_array;	//Memory pointer to the start of the tag array elements
	ident scenario_id;		//ID of the scenario tag
	uint32_t map_id;		//Not exactly sure, calling 'mapID' for now
	uint32_t tag_count;		//Number of tag array elements
	uint32_t vertice_count;	//Number of vertices
	uint32_t vertice_pointer;	//File pointer to the vertices
	uint32_t indice_count;	//Number of indices
	uint32_t indice_pointer;	//File pointer relative to the verticie pointer.
	uint32_t model_data_length;	//Total length of all model data
	uint32_t tag;			//'sgat' in ascii
} __attribute__ ((packed));

// Structure of individual index elements.
struct index_element
{
	uint32_t tag_group;		//Or first class
	uint32_t tag_parent;		//Or second class
	uint32_t third_class;		//Sounds about right
	ident id;			//Unique tag identity
	uint32_t tag_path;		//Memory pointer to the tag name/file path
	uint32_t tag_block;		//Memory pointer to the actual tag data
	char padding[4];
	uint32_t external;		//0 = false; resourse within file, 1 = indexed; resource outside of file
} __attribute__ ((packed));

/* Common Halo-specfic data types for the remainder of
	 this file. */

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
