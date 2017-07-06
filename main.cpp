#include <iostream>
#include "cache.h"

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
