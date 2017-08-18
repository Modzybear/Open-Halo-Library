# Open Halo Library
Copyright &copy; 2017 Andrew Burnett

## Description

An open library for parsing and decompiling Halo: Combat Evolved maps.

I've personally had a great interest in the blam! game engine since I was a teenager. I was heavily
involved in the later days of Halo modding at that time. Nowadays, many of the original modding
tools no longer work. The most popular, Eschaton, was written in a now unsupported BASIC-related
language. It now has many issues, some fatal. The lifetime of the Halo engine will likely come to
an end as newer operating systems introduce fatal issues in the binaries. This has already happened
with the OS X version.

Due to the above reasons, I have started this project to promote further reverse engineering
of Halo's data structures. As this project expands, I hope that many of the assets can be moved
into a newer engine. A reimplementation of the game in another engine may be the only way
to continue playing the original Halo.

## Usability

As of this release, OHL can be used to dump all tag files into the directories they were originally housed in.
These raw tag files can be edited or used for reverse engineering their data structures.
In maps with multiple SBSP tags, only the first one is extracted as of now.

The primary user of OHL would be anyone interested in reverse engineering
the blam! game engine, which runs the original Halo and the Stubb's Zombie game.

## Use

To test the current code, you can play with the testing main in map.cpp.
After the executable is compiled, you can feed in a map by typing:
"./ohl path/to/mapfile"

A new folder will appear named 'tags' in the same directory, and all directories and packed tag
data contained in the map file will be in the tags folder.

The code can be used in any project that needs to access specific data within a Halo cache file.
An example project may be a map editor, like Eschaton.

## Compiling the Testing Code

To compile, you'll need the BOOST library.
Use the compile flags: -lboost_filesystem -lboost_system

You may also utilize the makefile included in this repo by typing "make"
on a Linux-based system with this feature.

To learn more about BOOST: http://www.boost.org/

## License

Released on the BSD three-clause license. See LICENSE file for more information.

## Sister Project

For this project, I discovered I needed a separate project to generate
the code for the tag structures. The second project is located at:

https://github.com/Modzybear/Lazy-Grunt

## What I've Learned

Reverse engineering the data structures and putting them together in a way that makes
sense has been the biggest challenge. I've never created a project in Python, and I've
never made a program that generates code. In order to bring more Halo structures into
this project, I ended up doing both.

I've used Git is previous classes, but never really used it for a real project. It has
taught me a lot about proper version control. This is also my first time actually using
GitHub, which turns out to be awesome.

## TO DO

Continue to add the data structures for tags of particular interest.

Add extraction of multiple SBSP tags in maps with more than one.

CURRENT PROGRESS:
Basic cache file (.map) parsing is complete.
As of now, the cache class objects can only be created when given a
file path to a Halo map file. From there, you can get the tag count,
and use the extract_tag(index, path) function to extract tags.

The testing main in map.cpp uses the extract_tag function to extract all
tags in a map and places them in a new folder "tags/."

The tags folder becomes nearly identical to what the original Halo
developers must have saw.
