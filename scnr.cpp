#include "scnr.h"
#include <new>

scnr::scnr(char * buf, int off)
{
	buff = buf;
	offset = off;
	this->parse();
}

void scnr::parse()
{
	// Populate tag header
	tag_header = new (buff) scnr_header;

	// Populate sbsps
	structure_bsps = new (buff +
	(tag_header->structure_bsps.pointer - offset - RETAIL_MEMORY_ADDRESS))
	structure_bsps_block[tag_header->structure_bsps.block_count];
}
