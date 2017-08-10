#ifndef CACHE_H
#define CACHE_H

/*
Copyright 2017 Andrew Burnett

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "datatypes.h"
#include "scnr.h"

const uint32_t RETAIL_MEMORY_ADDRESS = 0x40440000;
const uint32_t DEMO_MEMORY_ADDRESS = 0x4BF10000;
const uint32_t HEADER_LENGTH = 0x800;

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

class cache
{
	public:
		cache (char *);			// init
		~cache ();			// Clean things up
		bool open (char *);		// Parse a map when given its file path
		bool parse (FILE *);		// Do the actual parsing
		bool extract_tag(int, std::string root_path = "tags/");
		int tag_count();
		char * buffer(int);


	private:
		// Useful data
		header * m_header;		// Map header
		index_header *i_header;	// Index header
		index_element *elements;	// Index elements

		// All the data sections of a Halo cache file
		char *head_buffer;		// Stores the header data
		char *SBSP_buffer;		// Stores all BSP data, scenario must be read before its populated
		char *resource_buffer;	// Bitmaps and sounds that are stored internally
		char *model_data;		// Verts and their triangles
		char *map_buffer;		// All tag data
		scnr * scenario; // Supertag
};

#endif
