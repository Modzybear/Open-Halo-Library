# Open Halo Library
Copyright &copy; 2017 Andrew Burnett

THE CURRENT CODE IS FOR LEARNING PURPOSES ONLY.
NOT READY FOR GENERAL USE.

## Description

An open library for parsing and decompiling Halo: Combat Evolved maps.

## Use

As of this release, OHL can be used to dump all tag files into the directories they were originally housed in. These raw tag files can
be edited or used for reverse engineering their data structures. This dump excludes
SBSP tags, which are stored differently.

The primary user of OHL would be anyone interested in reverse engineering
the blam! game engine, which runs the original Halo and the Stubb's Zombie game.

## Compiling

To compile, you'll need the BOOST library.
Use the compile flags: -lboost_filesystem -lboost_system
You may also utilize the makefile included in this rep. by typing "make"
on a Linux-basd system with this feature.

## License

Released on the BSD three-clause license. See LICENSE file for more information.

## TO DO

Continue to add the data structures for tags of particular interest.

WEEK THREE PROGRESS REPORT:
Basic cache file (.map) parsing is complete. Still need to
read and use the raw data sections of the file. This cannot be
done until parsing of certain tag files themselves is completed.

As of now, the cache class objects can only be created when given a
file path to a Halo map file. From there, you can get the tag count,
and use the extract_tag(index, path) function to extract tags.

The testing main in cache.cpp uses the extract_tag function to extract all
tags in a map and places them in a new folder "tags/."

The tags folder becomes nearly identical to what the original Halo
developers must have saw.
