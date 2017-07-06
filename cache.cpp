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

cache::cache ()
{

}

bool
cache::open (char *file_path)
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


bool
cache::parse (FILE * map)
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

void
cache::list_tags ()
{
  for (int i = 0; i < i_header->tag_count; ++i)
    {
      char *tag_path =
	new (map_buffer +
	     (elements[i].tag_path - RETAIL_MEMORY_ADDRESS)) char;
      cout << tag_path << endl;
    }
}

cache::~cache ()
{
  if (map_buffer)
    {
      delete map_buffer;
    }
}

int
main (int argc, char *argv[])
{
  if (argc < 2)
    {
      cout << "No map file given.";
    }
  else
    {
      cache cache_file;
      cache_file.open (argv[1]);
      cout << endl;
      cache_file.list_tags ();
    }
}

#endif
