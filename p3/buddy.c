/**
 * Implementation of a memory allocator based on the Buddy System.
 * Author: Mario Torres
 * Date: Mon Sep 19 19:15:51 MDT 2022
 */
 
#include "buddy.h"

int buddy_init(void) { 
	// Getting size of memory
	base = sbrk(DEFAULT_MAX_MEM_SIZE);

	// Creating header pointer
	struct block_header *p = (struct block_header *) base;

	// Update information for each array position
	for (int i = 0; i <= 29; i++) {
		// Updating final position's information
		if (i == 29) {
			avail[i].next = p;
			avail[i].prev = p;
			avail[i].kval = i;
			avail[i].tag = UNUSED;
		} else // Upading position's 0 - 28 information
		avail[i].next = &avail[i];
		avail[i].prev = &avail[i];
		avail[i].kval = i;
		avail[i].tag = UNUSED;
	}	

	// Updating the headers information
	p->next = &avail[29];
	p->prev = &avail[29];
	p->kval = 29;
	p->tag = FREE;

	return TRUE;
}

void *buddy_malloc(size_t size)
{
	// Verify that buddy_init() was called
	if (base == NULL) {
		return NULL;
	}

	// Variables
	int r, i, j;
	struct block_header *p, *p2, *p3, *new;
	int lgSize = 0;
	int free = FREE;
	void *retVal;

	// Add header size to size
	size += sizeof(struct block_header);
	size -= 1;

	// Figuring out lgSize
	while (size > 0) {
		size = size >> 1;
		lgSize++;
	}

	// verify lgSize size
	if (lgSize > 29) {
		return NULL;
	}
}

void buddy_free(void *ptr) 
{
}

void printBuddyLists(void)
{
}

/* vim: set ts=4: */
