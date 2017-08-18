/*
Copyright 2017 Andrew Burnett

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "map.h"

// Take in a path to cache file, for use in utility functions.
map::map(char * file)
{
  cache_file = new cache(file);
}

// Use the cache object to extract packed tag data to a specified folder.
// Takes in an index, the position of the index element for the tag.
// Optionally takes in a path to extract the tag to. Default is '/tags.'
bool map::extract_tag(int index, std::string root_path)
{
	// Sanity checks
  if (!cache_file) { return false; }
	if (index > cache_file->tag_count() - 1) { return false; }

	// Get the string representing the directory that holds the tag
	std::string path = cache_file->tag_path(index);

	// Check for invaild (non-Windows) path
	if (path.find("/") != std::string::npos)
	{
		std::cout << "Failed to extract tag with invalid path: " << path;
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
  int grp = cache_file->tag_group(index);
  std::string group((char *) &grp);
  group = group.substr(0, 4); // Fix the termination
  std::reverse(group.begin(), group.end());
  path += group;

  // Create tag file and copy data
  FILE * tag;
  tag = fopen (path.c_str(), "w+");

  int size = cache_file->tag_length(index);

  // Handle SBSP packed tag data extraction. The SBSP data is stored in the resources buffer.
  if (group == "sbsp")
  {
    int sbsp_index = 0;
    size = cache_file->scenario->structure_bsps[sbsp_index].bsp_size;
    fwrite(cache_file->resource_buff() + cache_file->scenario->structure_bsps[sbsp_index].bsp_start, sizeof(char), size, tag);
  }
  else
  {
    fwrite(cache_file->buffer(index), sizeof(char), size, tag);
  }
  fclose(tag);
}

// Iterate through all the tags and extract them
bool map::extract_all(std::string root_path)
{
  for (int i = 0; i < cache_file->tag_count() - 1; ++i)
  {
    extract_tag(i, root_path);
  }
}


// Testing main tag extraction
int main (int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cout << "No map file given.";
	}
	else
	{
    map map_obj(argv[1]);
		map_obj.extract_all();
	}
}
