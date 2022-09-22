/**
 * Implementation of a memory allocator based on the Buddy System.
 * Author: Mario Torres
 * Date: Mon Sep 19 19:15:51 MDT 2022
 */
 
#include "buddy.h"

int buddy_init(void) { 
	// Variables
	int i;
	// Getting size of memory
	base = sbrk(DEFAULT_MAX_MEM_SIZE);

	// Creating header pointer
	struct block_header *p = (struct block_header *) base;

	// Update information for each array position
	for (i = 0; i <= 29; i++) {
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

void *buddy_malloc(size_t size) {
	// Verify that buddy_init() was called
	if (base == NULL) {
		return NULL;
	}
	
	// Variables
	int r, i, j;
	struct block_header *p, *p2, *p3, *new;
	int lgSize = 0;
	int free = FALSE;
	void *retVal;

	// Add header size to size
	size += sizeof(struct block_header);
	size -= 1;

	// Figuring out lgSize
	while (size > 0) {
		size = size >> 1;
		lgSize++;
    }

	// Verify lgSize size
	if (lgSize > 29) {
		return NULL;
	}

	// Start looking for available block
	for (i = lgSize; i < 30; i++) {
		p = &avail[i];
		while (p->next->tag != UNUSED) {
			p = p->next;
			if (p->tag == FREE) {
				free = TRUE;
				break;
			}
		}
		if (free) {
			break;
	}
	}

	// Verify that something was found
	if (!free) {
		return NULL;
	}

	// Check to see if free block is at avail[lgSize]
	if (p->kval == lgSize) {
		struct block_header *t1, *t2;
		p->tag = RESERVED;
		t1 = p->next;
		t2 = p->prev;
		t1->prev = t2;
		t2->next = t1;
		retVal = (void *)((char *)p + sizeof(struct block_header));
		return retVal;
	}

	// If not save avail level
	j = i;

	// Finding memory in block at avail level
	r = DEFAULT_MAX_MEM_SIZE;
	while (i < 29) {
		r = r >> 1;
		i++;
	}

	// Update next and prev pointers
	while (lgSize < j) {
		if (p->next != NULL && p->prev != NULL) {
			p2 = p->prev;
			p3 = p->next;
			
			p2->next = p3;
			p3->prev = p2;

			// Since p is being used, remove
			p->next = NULL;
			p->prev = NULL;
			p->tag = RESERVED;
		}

		// Adjust r and j
		r = r >> 1;
		j--;
		
		// Making new header
		new = (struct block_header *)(base + r);

		// Adjusting values
		p->kval = j;
		new->kval = j;
		new->tag = FREE;

		// Adding to linked list
		p2 = &avail[j];
		p3 = p2->next;
		
		// Adjusting pointers
		p2->next = new;
		new->prev = p2;
		new->next = p3;
		p3->prev = new;
	}

	// retVal
	retVal = (void *)((char *)p + sizeof(struct block_header));

	return retVal;
}

void buddy_free(void *ptr) {
	// Variables
	struct block_header *p1;
	struct block_header *p2;
	long x, y;
	
	// Assigning variables
	p1 = (struct block_header *) ((char *)ptr - sizeof(struct block_header));
	x = (long)p1 - (long)base;
	y = (unsigned long long)(x)^(1ULL<<(p1->kval));
	p2 = (struct block_header *)((long)p1 + (long)y);
	
	// Looking to free blocks
	while (p2->tag == FREE && p2->kval == p1->kval) {
		// Adjust p2 data
		struct block_header *t1, *t2;
		t1 = p2->prev;
		t2 = p2->next;
		t1->next = t2;
		t2->prev = t1;
		
		// Increment kval and try to find next buddy
		p1->kval = (short)p1->kval + 1;

		// Find buddy address
		y = (unsigned long long)(x)^(1ULL<<(p1->kval));
		p2 = (struct block_header *)((long)p1 + (long)y);
	}

	if (p1 > p2 && p1->kval != 29) {
		p1 = p2;
	}
	
	// Adjusting pointers
	p1->tag = FREE;
	struct block_header *t = avail[p1->kval].next;
	avail[p1->kval].next = p1;
	t->prev = p1;
	p1->prev = &avail[p1->kval];
	p1->next = t;
	
}

void printBuddyLists(void) {
	// Variables
	int i;
	int count = 0;
	struct block_header *p, *s;

	// Looping through each list
	for (i = 0; i < 30; i++) {
		p = &avail[i];
		s = p;
		printf("List %d: head = %p", i, p);
		while (1) {
			p = p->next;
			if (p == s) {
				printf(" --> head = %p", p);
				break;
			} else {
				printf(" --> [tag=%d, kval=%d, addr=%p]", p->tag, p->kval, p);
				if (p->tag == FREE) {
					count++;
			}
			}
		}
		printf("\n");
	}
	printf("\nNumber of available blocks = %d \n", count);
}

/* vim: set ts=4: */
