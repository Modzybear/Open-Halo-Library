#ifndef HDATA_H
#define HDATA_H

/*
 ** hdata.h
 ** Andrew Burnett 2014 (Modzy)
 ** Halo basic data types
 ** BloomEngine source
 */

#include <stdint.h>

using namespace std;

struct blockPointer{
	uint32_t blockCount;
	uint32_t pointer;
	char editorData[4]; //only used internally by Guerilla.
} __attribute__ ((packed)) ;

struct ident{
	uint16_t id;
	uint16_t tagNumber;
} __attribute__ ((packed)) ;

struct reference{
	uint32_t tagGroup; //Or 'first class'
	uint32_t namePointer; //Memory pointer to tag name/file path
	char referencePathLength[4]; //only used internally by Guerilla.
	ident id;
} __attribute__ ((packed)) ;

struct bound {
	float from;
	float to;
} __attribute__ ((packed)) ;

struct vertex {
	float x;
	float y;
	float z;
} __attribute__ ((packed)) ;

struct radianRotation {
	float y;
	float p;
	float r;
} __attribute__ ((packed)) ;

#endif
