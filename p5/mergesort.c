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
void mergesort(int left, int right) {
		// Base case
		if (left >= right) {
				return;
		}

		// Break in half and call recursively 
		int middle = (left + right) / 2;
		mergesort(left, middle);
		mergesort(middle + 1, right);
		
		// Merge
		merge(left, middle, middle + 1, right);
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg) {
		// Variables
		pthread_t t1, t2;
		struct argument *arg1, *arg2, *orig;

		// Assign value to orig
		orig = (struct argument *)arg;

		// Checking to see if level is equal to cutoff
		if (orig->level == cutoff) {
				// Call mergesort
				mergesort(orig->left, orig->right);
				// Return null
				return NULL;
		}

		// Verifying left is not greater than or equal to right
		if (orig->left >= orig->right) {
				// Return null
				return NULL;
		}

		// Geting middle
		int middle = (orig->left + orig->right) / 2;
		
		// Updating arg1 and arg2 for recursion call
		arg1 = buildArgs(orig->left, middle, orig->level + 1);
		arg2 = buildArgs(middle + 1, orig->right, orig->level + 1);

		// Recursion
		pthread_create(&t1, NULL, parallel_mergesort, arg1);
		pthread_create(&t2, NULL, parallel_mergesort, arg2);

		// Join and merge
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		merge(arg1->left, arg1->right, arg2->left, arg2->right);

		// Free memory
		free(arg1);
		free(arg2);

		// Return null
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
