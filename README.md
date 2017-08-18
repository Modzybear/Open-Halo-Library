# Open Halo Library
Copyright &copy; 2017 Andrew Burnett

## Description

An open library for parsing and decompiling Halo: Combat Evolved maps.

## Purpose

As of this release, OHL can be used to dump all tag files into the directories they were originally housed in.
These raw tag files can be edited or used for reverse engineering their data structures.
In maps with multiple SBSP tags, only the first one is extracted as of now.

The primary user of OHL would be anyone interested in reverse engineering
the blam! game engine, which runs the original Halo and the Stubb's Zombie game.

## Use

To use the current code, you can play with the testing main in map.cpp.
After the executable is compiled, you can feed in a map by typing:
"./ohl <path to mapfile>"

A new folder will appear named 'tags' in the same directory, and all directories and packed tag
data contained in the map file will be in the tags folder.

## Compiling

To compile, you'll need the BOOST library.
Use the compile flags: -lboost_filesystem -lboost_system
You may also utilize the makefile included in this repo by typing "make"
on a Linux-based system with this feature.

## License

Released on the BSD three-clause license. See LICENSE file for more information.

## TO DO

Continue to add the data structures for tags of particular interest.
Add extraction of multiple SBSP tags in maps with more than one.

CURRENT PROGRESS:
Basic cache file (.map) parsing is complete.
As of now, the cache class objects can only be created when given a
file path to a Halo map file. From there, you can get the tag count,
and use the extract_tag(index, path) function to extract tags.

The testing main in cache.cpp uses the extract_tag function to extract all
tags in a map and places them in a new folder "tags/."

The tags folder becomes nearly identical to what the original Halo
developers must have saw.
