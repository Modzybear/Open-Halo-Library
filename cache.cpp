#ifndef CACHE_CPP
#define CACHE_CPP

/*
   Andrew Burnett
   Copywrite (C) Andrew Burnett
   Released under GLP license
   June 2017
 */

#include <iostream>
#include "cache.h"
#include <boost/filesystem.hpp>

cache::cache (char * file)
{
	this->open(file);
}

bool cache::open (char * file_path)
{
	FILE *map;
	map = fopen (file_path, "r");
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


bool cache::parse (FILE * map)
{
	m_header = new header;
	fseek (map, 0, SEEK_SET);
	fread ((char *) m_header, 0x1, 0x800, map);	// Read into buffer

	fseek (map, m_header->tag_array, SEEK_SET);	// Go to map data
	map_buffer = new char[m_header->cache_length];	// Create the map buffer
	fread (map_buffer, 0x1, m_header->cache_length, map);	// Read into buffer

	// Read the index within the tag buffer
	i_header = new (map_buffer) index_header;	// Parse the header
	// Get all tag info:
	elements =
		new (map_buffer +
				(i_header->element_array -
				 RETAIL_MEMORY_ADDRESS)) index_element[i_header->tag_count];
	return true;
}

bool cache::extract_tag(int index, std::string root_path)
{
	// Sanity check
	if (index > i_header->tag_count - 1) { return false; }

	// Get the string representing the directory that holds the tag
	char * raw_path =
		new (map_buffer +
				(elements[index].tag_path - RETAIL_MEMORY_ADDRESS)) char;
	std::string path(raw_path);
	raw_path = NULL; // The buffer is owned by another object

	// Check for invaild (non-Windows) path
	if (path.find("/") != std::string::npos)
	{
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

	// SBSP data is stored outside the tag data block.
	// Therefore we cannot extract it yet. Skip if called on SBSP tag.
	if (group == "sbsp")
	{
		return false;
	}

	// Create tag file and copy data
	FILE * tag;
	tag = fopen (path.c_str(), "w+");

	int size = elements[index + 1].tag_block - elements[index].tag_block;
	if (index >= i_header->tag_count - 2)
	{
		size = (m_header->cache_length + RETAIL_MEMORY_ADDRESS) - elements[index].tag_block;
	}

	fwrite(map_buffer + (elements[index].tag_block - RETAIL_MEMORY_ADDRESS), sizeof(char), size, tag);
	fclose(tag);
}

int cache::tag_count()
{
	return i_header->tag_count;
}

cache::~cache ()
{
	if (map_buffer)
	{
		delete map_buffer;
	}
}

int main (int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "No map file given.";
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
