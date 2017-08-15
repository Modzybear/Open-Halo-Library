#ifndef CACHE_CPP
#define CACHE_CPP

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
#include <stdio.h>
#include <vector>
#include <string>
#include "cache.h"
#include <boost/filesystem.hpp>

// Take in a file path to a map file and parse it into
// the cache object upon object creation.
cache::cache (char * file)
{
	bool success = this->open(file);
	if (!success)
	{
		// The map file failed to load, therefore the object must now be NULL.
		*this = NULL;
	}
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
	m_header = new header;
	fseek (map, 0, SEEK_SET);
	fread ((char *) m_header, 0x1, 0x800, map);	// Read into buffer

	fseek (map, m_header->tag_array, SEEK_SET);	// Go to map data
	assets = new char[m_header->cache_length];	// Create the map buffer
	fread (assets, 0x1, m_header->cache_length, map);	// Read into buffer
	resources = new char[m_header->tag_array];
	fseek (map, 0, SEEK_SET);
	fread (resources, 0x1, m_header->tag_array, map);

	// Read the index within the tag buffer
	i_header = new (assets) index_header;	// Parse the header
	// Get all tag info:
	elements =
		new (assets +
				(i_header->element_array -
				 RETAIL_MEMORY_ADDRESS)) index_element[i_header->tag_count];

  // Read SBSPs from the scenario tag
	scenario = new scnr(buffer(0), offset(0));

	/* Testing code to see if the structures line up with the actual data. */
	int sky_count = scenario->tag_header->structure_bsps.block_count;
	if (sky_count > 1)
	{
		std::cout << "There are "<< sky_count << " sbsp tags in the scenario.\n";
	}
	else
	{
		std::cout << "There is "<< sky_count << " sbsp tag in the scenario.\n";
	}

	int sbsp_start = scenario->structure_bsps[0].bsp_start;
	std::cout << "The sbsp starts at: " << sbsp_start << std::endl;

	return true;
}

// Use the loaded map to extract packed tag data to a specified folder.
// Takes in an index, the position of the index element for the tag.
// Optionally takes in a path to extract the tag to. Default is '/tags.'
bool cache::extract_tag(int index, std::string root_path)
{
	// Sanity checks
	if (this == NULL) { return false; }
	if (index > i_header->tag_count - 1) { return false; }

	// Get the string representing the directory that holds the tag
	char * raw_path =
		new (assets +
				(elements[index].tag_path - RETAIL_MEMORY_ADDRESS)) char;
	std::string path(raw_path);
	raw_path = NULL; // The buffer is owned by another object

	// Check for invaild (non-Windows) path
	if (path.find("/") != std::string::npos)
	{
		std::cout << "Fail to extract tag with invalid path: " << path;
		return false;
	}

	// Fix the Windows-based path string and
	// get the containing directory
	std::replace(path.begin(), path.end(), '\\', '/');
	path = root_path + path;
	int dir_pos = path.find_last_of("/");
	std::string dir_path = path.substr(0, dir_pos);

	// Create the directories
	boost::filesystem::create_directories(dir_path);

	// Create tag file
	path += ".";
	std::string group = std::string((char *) &elements[index].tag_group);
	group = group.substr(0, 4);
	std::reverse(group.begin(), group.end());
	path += group;

	// Create tag file and copy data
	FILE * tag;
	tag = fopen (path.c_str(), "w+");

	int size = elements[index + 1].tag_block - elements[index].tag_block;
	if (index >= i_header->tag_count - 2)
	{
		size = (m_header->cache_length + RETAIL_MEMORY_ADDRESS) - elements[index].tag_block;
	}

	// Handle SBSP packed tag data extraction. The SBSP data is stored in the resources buffer.
	if (group == "sbsp")
	{
		int sbsp_index = 0;
		size = scenario->structure_bsps[sbsp_index].bsp_size;
		fwrite(resources + scenario->structure_bsps[sbsp_index].bsp_start, sizeof(char), size, tag);
	}
	else
	{
		fwrite(assets + offset(index), sizeof(char), size, tag);
	}
	fclose(tag);
}

// Return the number of tags in the cache file.
int cache::tag_count()
{
	return i_header->tag_count;
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

// Testing main for unit testing.
int main (int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "No map file given.";
	}
	else
	{
		cache cache_file(argv[1]);

		// Test for extracting all tag files
		for (int i = 0; i < cache_file.tag_count() - 1; ++i)
		{
			cache_file.extract_tag(i);
		}
	}
}

#endif
