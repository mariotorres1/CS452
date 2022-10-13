/**
 * This file implements parallel mergesort.
 * Author: Mario Torres
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend) {
		// Variables
		int size = rightend - leftstart + 1;
		int i = leftstart;
		int left = leftstart;
		int right = rightstart;

		// Loop through
		while (left <= leftend && right <= rightend) {
				// Making sure leftstart isn't past rightstart
				if (A[left] <= A[right]) {
						B[i] = A[left];
						left++;
				} else {
						B[i] = A[right];
						right++;
				}
				i++;
		}

		// memcopy
		memcpy(&B[i], &A[left], (leftend - left + 1) * sizeof(int));
		memcpy(&B[i], &A[right], (rightend - right + 1) * sizeof(int));
		memcpy(&A[leftstart], &B[leftstart], size * sizeof(int));
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
