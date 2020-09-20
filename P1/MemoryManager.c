#include <stdio.h>
#include <stdlib.h>

/**
 * Compares two numbers and returns a positive integer, 0 or 
 * a negative integer if the first number is greater than, equal to
 * or less than the second number.
 * Assumes the numbers are of the type int.
 * Used when invoking the quicksort function.  
 */
int compare (const void * a, const void * b)
{
   return (*(int*)a - *(int*)b);
}


/**
 * Takes in an array of integers and the number of elements in the array 
 * as arguments.
 * Then it will sort and return the median of the sorted array. 
 * To keep things simple, it always returns
 * the element at index arr_size/2 even though the 
 * array size is even.
 */
int return_median(int *arr, int size)
{
   qsort(arr, size, sizeof(int), compare);
   return arr[size/2];
}


/**
 * Takes in a random number and maps it to the
 * range [100000 - 120000)
 */
int get_iteration_count(int rand)
{
    return (rand % 20000) + 100000;     
}

/**
 * Takes in a random number and maps it to the 
 * range [1000 - 1500)
 */
int get_arr_size(int rand)
{
    return (rand % 500) + 1000;
}


/**
 * This is the method that you need to implement.
 * Implement the following steps in the given order.
 *
 *  1. Generate the number of iterations
 *      - Generate a random number. Map it to the range [100000 - 120000) using the 
 *      utility function 'get_iteration_count'.
 * 
 * 2. For each iteration:
 *      2.a Generate an array size - Generate a random number and map it to the range [1000 - 1500) using
 *          the utility function 'get_arr_size'.
 * 
 *      2.b Allocate memory for the array in the heap.
 *
 *      2.c Populate the array with random numbers.
 *
 *      2.d Get the median of the array using the function 'return_median'.
 *
 *      2.e Check if the median is divisible by 13.
 *
 *      2.f Return the number of medians that were divisible by 13.
 *
 */
int get_running_count()
{
	// Create return variable that counts medians divisible by 13
	int running_count = 0;
	// Use rand to generate the number of times to iterate
	int iter_count = get_iteration_count(rand());
	// Print the number of times you plan to iterate
	printf("[MemoryManager] Number of Iterations: %d\n", iter_count);
	for(int i = 0; i < iter_count; i++){
		// Arr length is used several times so store it in a var
		int arr_length = get_arr_size(rand());
		// Dynamically create an int array with malloc
		int *ran_array = (int *)malloc(sizeof(int)*arr_length);
		// Loop through the array and generate random values for it
		for(int j = 0; j < arr_length; j++){
			ran_array[j] = rand();
		}
		// Get median of array
		int median = return_median(ran_array,arr_length);
		// Check if its divisible by 13, if so increment running count
		if(median % 13 == 0){
			++running_count;
		}
		// Free array from heap
		free(ran_array);
		// Set pointer to NULL so it cant be accessed anymore
		ran_array = NULL;
	}
	// Return running count number
	return running_count;
}
