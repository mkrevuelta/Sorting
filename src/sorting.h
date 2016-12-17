/*
    Copyright (c) 2013, Martin Knoblauch Revuelta
    See accompanying LICENSE
    
    -------------------------------------------------------------
    sorting.h
    
    Main header file containing the definition of the data type
    to sort and the prototypes of the sorting functions
    -------------------------------------------------------------
*/

#ifndef _SORTING_MKR_H_
#define _SORTING_MKR_H_

#include <stdint.h>

typedef double sorteddatatype;

void combsort_cocktail_sqrt2_primes (
                    sorteddatatype A[],    // Array to be sorted
                    uint32_t len);         // Size of the array

void smoothsort (sorteddatatype A[],       // Array to be sorted
                 uint32_t num);            // Size of the array

void smoothsort_fib_1 (sorteddatatype A[], // Array to be sorted
                       uint32_t num);      // Size of the array

void smoothsort_pow2_1 (
                    sorteddatatype A[],    // Array to be sorted
                    uint32_t len);         // Size of the array

void bubblesort (sorteddatatype A[],       // Array to be sorted
                 uint32_t num);            // Size of the array

void bubblesort_poor_C (
                 sorteddatatype A[],       // Array to be sorted
                 uint32_t num);            // Size of the array

void bubblesort_chained_swaps (
                 sorteddatatype A[],       // Array to be sorted
                 uint32_t num);            // Size of the array

void insertionsort_simple (
                 sorteddatatype A[],       // Array to be sorted
                 uint32_t num);            // Size of the array

void insertionsort_chained_swaps (
                 sorteddatatype A[],       // Array to be sorted
                 uint32_t num);            // Size of the array

void insertionsort_binary_search (
                 sorteddatatype A[],       // Array to be sorted
                 uint32_t num);            // Size of the array

void insertionsort_biased_binary_search (
                 sorteddatatype A[],       // Array to be sorted
                 uint32_t num);            // Size of the array

void heapsort (sorteddatatype A[],         // Array to be sorted
               uint32_t num);              // Size of the array

void heapsort_floyd (sorteddatatype A[],   // Array to be sorted
                     uint32_t num);        // Size of the array

void quicksort (sorteddatatype A[],        // Array to be sorted
                uint32_t num);             // Size of the array

void quicksort_median_of_medians (
                 sorteddatatype A[],       // Array to be sorted
                 uint32_t num);            // Size of the array

#endif // _SORTING_MKR_H_

