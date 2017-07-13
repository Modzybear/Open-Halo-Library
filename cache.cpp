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
		fclose (map);
	}
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

	extract_paths();
	return true;
}

void cache::list_tags ()
{
	boost::filesystem::path dir("tags");
	boost::filesystem::create_directory(dir);
	for(int i = 0; i < i_header->tag_count - 1; ++i)
	{
		std::string curr = "tags/";
		for(int j = 0; j < paths[i].size() - 1; ++j)
		{
			curr += paths[i][j];
			boost::filesystem::path direct(curr);
			boost::filesystem::create_directory(direct);
			curr += "/";
		}

		FILE *tag;
		curr += paths[i][paths[i].size() - 1];
		curr += ".";
		char group[5];
		strncpy(group, (char *) &elements[i].tag_group, 4);
		group[4] = '\0';
		std::string grp(group);
		std::reverse(grp.begin(), grp.end());
		curr += grp;
		tag = fopen (curr.c_str(), "w+");
		//fwrite(buffer, sizeof(char), sizeof(buffer), tag)
		int size = 0;
		if (i >= i_header->tag_count - 2)
		{
			size = (m_header->cache_length + RETAIL_MEMORY_ADDRESS) - elements[i].tag_block;
		}
		else
		{
			size = elements[i + 1].tag_block - elements[i].tag_block;
		}
		fwrite(map_buffer + (elements[i].tag_block - RETAIL_MEMORY_ADDRESS), sizeof(char), size, tag);
		fclose(tag);
	}
}

void cache::extract_paths(int index)
{
	if (index > i_header->tag_count - 1) { return; }

	char *tag_path =
		new (map_buffer +
				(elements[index].tag_path - RETAIL_MEMORY_ADDRESS)) char;
	std::string path(tag_path);

	vector<std::string> directories;
	int p = 0;

	while((p = path.find("\\")) != std::string::npos)
	{
		directories.push_back(path.substr(0, p));
		path.erase(0, p + 1);
	}
	directories.push_back(path);
	paths.push_back(directories);

	extract_paths(index + 1);
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
		cache_file.list_tags ();
	}
}

#endif
