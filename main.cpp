/*
	Andrew Burnett
	Copywrite (C) Andrew Burnett
	Released under GLP license
	June 2017
*/

#include "cache.h"
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {
	if (argc < 2) {
		cout << "No map file given.";
	} else {
		Cache cache;
		char * filePath = new char[3];
		cache.test();
	}
}
