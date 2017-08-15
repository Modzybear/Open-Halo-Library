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

/*		*** Cache class ***
Halo maps are stored as cache files. These files have three parts:
- Cache header
- Resource buffer
- Asset buffer

The map geometry, object models, and possibly internalized bitmaps/sounds
are stored within the resource buffer. For simplicity, the cache header can be
included in this buffer.

The index/list of all tags in the cache file and the packed tag structures
themselves are stored within the asset buffer.

The cache class allows for basic map parsing and access to the major sections
of the two buffers.
*/

//#include <stdio.h>
#include "datatypes.h"
#include "scnr.h"

class cache
{
	public:
		cache (char *);			// init
		~cache ();			// Clean things up
		bool open (char *);		// Parse a map when given its file path
		bool parse (FILE *);		// Do the actual parsing
		bool extract_tag(int, std::string root_path = "tags/"); // Extract tag to folder
		int tag_count(); // Return the number of tags in the map
		char * buffer(int); // TEMP method to get the resource buffer
		int offset(int); // TEMP method to get a tag's memory offset given its index number


	private:
		// Useful data
		header * m_header;		// Map header
		index_header * i_header;	// Index header
		index_element * elements;	// Index elements

		// The scenario must be parsed with the cache file to extract sbsp tags
		scnr * scenario; // The supertag

		// All the data sections of a Halo cache file
		char * resources;	// Resource buffer
		char * assets;		// Asset buffer
};

#endif
