 /*
 Copyright 2017 Andrew Burnett

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*		** Cache class ***
Implements the cache class methods.
*/

#include <iostream>
#include "cache.h"

// Take in a file path to a map file and parse it into
// the cache object upon object creation.
cache::cache (char * file)
{
	bool success = this->open(file);
}

// Takes in the file path to a map file and calls parse to
// populates the cache object.
// Returns false if the map file failed to be parsed.
bool cache::open (char * path)
{
	FILE * map;
	map = fopen (path, "r");
	if (map == NULL)
	{
		perror ("Error opening file");
		return false;
	}
	else
	{
		return cache::parse (map);
	}
	fclose (map);
}

// Takes in a file object, a map file, and parses the file to populates
// the cache object.
bool cache::parse (FILE * map)
{
	// Get the header to load the map
	m_header = new header;
	fseek (map, 0, SEEK_SET);
	fread ((char *) m_header, 0x1, 0x800, map);	// Read into buffer

	// Make sure this map is a retail version map
	if (m_header->head != 0x68656164) // 'daeh'
	{
		return false;
	}
	else
	{
		MEM_OFFSET = RETAIL_MEMORY_ADDRESS;
	}

	// Read the map into memory
	resources = new char[m_header->tag_array];
	fseek (map, 0, SEEK_SET);
	fread (resources, 0x1, m_header->tag_array, map);
	//fseek (map, m_header->tag_array, SEEK_SET);	// Go to map data
	assets = new char[m_header->cache_length];	// Create the map buffer
	fread (assets, 0x1, m_header->cache_length, map);	// Read into buffer


	// Read the index within the asset buffer
	i_header = new (assets) index_header;	// Parse the header

	// Get all tag info:
	elements =
		new (assets +
				(i_header->element_array -
				 MEM_OFFSET)) index_element[i_header->tag_count];

  // Read SBSPs from the scenario tag
	scenario = new scnr(buffer(0), offset(0));

	return true;
}

// Return the number of tags in the cache file.
int cache::tag_count()
{
	return i_header->tag_count;
}

// Return the tag path with given index.
std::string cache::tag_path(int index)
{
	char * raw_path =
		new (assets +
				(elements[index].tag_path - RETAIL_MEMORY_ADDRESS)) char;
	std::string path(raw_path);
	raw_path = NULL; // The buffer owns this memory.
	return path;
}

// Return the group of the tag at index.
int cache::tag_group(int index)
{
	return elements[index].tag_group;
}

// Return the size of the tag at index.
int cache::tag_length(int index)
{
	int size = 0;
	if (tag_group(index) == 0x73627370)
	{
		return size;
	}

  if (index >= i_header->tag_count - 2)
  {
    size = (m_header->cache_length + MEM_OFFSET) - elements[index].tag_block;
  }
	else
	{
		size = elements[index + 1].tag_block - elements[index].tag_block;
	}

	return size;
}

// TEMP
char * cache::resource_buff()
{
	return resources;
}

// TEMP
char * cache::buffer(int index)
{
	return assets + offset(index);
}

// TEMP
int cache::offset(int index)
{
	return elements[index].tag_block - RETAIL_MEMORY_ADDRESS;
}

// Clear the buffer but not really because I'll write a smart destructor later.
cache::~cache ()
{
	if (assets)
	{
		delete assets;
	}
}
