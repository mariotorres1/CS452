/**
 * This file implements parallel mergesort.
 * Author: Mario Torres
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
}

/* this function will be called by parallel_mergesort() as its base case. */
void mergesort(int left, int right){
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level) {
		// Create struct 
		struct argument * arg = (struct argument *)malloc(sizeof(struct argument));
		// Update arg values
		arg->left = left;
		arg->right = right;
		arg->level = level;

		// Return arg
		return arg;
}

/* vim: set ts=4: */
