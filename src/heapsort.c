/*
    Copyright (c) 2013, Martin Knoblauch Revuelta
    See accompanying ../LICENSE
    
    ---------------------------------------------------------------
    heapsort.c
    
    Implementation of heap sort. There are two versions of
    it in this file:
    
       1) The first one is the bare algorithm. It uses the same
          sift_in() for both phases ---building the heap and
          consuming it---. This implementation has an interesting
          property: it takes only O(N) time when all input data
          are equal. This means it is technically O(N) best-case,
          but this "best case" is not the general "already sorted
          data". It is a very specific instance of it ("already
          sorted _and_ equal")
          
       2) The second one includes an optimization proposed by
          Robert W. Floyd: In the second phase, while reinserting
          the element taken from the end of the heap, this
          version pushes it down to the bottom inconditionally.
          Then it undoes part of that if necessary. But it is
          not necessary most of the times. This saves some
          comparisons in the way down. Though, note that this
          implementation always takes O(N log N) time
    ---------------------------------------------------------------
*/

#include "sorting.h"

static inline void sift_in (
        sorteddatatype * H,     // Heap goes from H[1] to H[num]
        uint32_t         num,   // Current size of the heap
        uint32_t         i);    // Element to push down

static inline void sift_in_floyd (
        sorteddatatype * H,     // Heap goes from H[1] to H[num]
        uint32_t         num,   // Current size of the heap
        sorteddatatype   tmp);  // Value to be inserted
                                // (Assume that H[1] is empty)

void heapsort (sorteddatatype A[],         // Array to be sorted
               uint32_t num)               // Size of the array
{
    sorteddatatype * H;   // We will access the array through H
    sorteddatatype tmp;   // Temporary variable for swaps
    uint32_t i;           // Next element to insert in the heap

    if (num < 2)
        return;
                   // Access the array as { H[1], ... H[num] }
    H = A - 1;     // This way, the children of H[x] are
                   // H[2*x] and H[2*x+1]

    // 1st: HEAPIFY
                              // Build a valid max heap by
    for (i=num>>1; i; i--)    // pushing down the small elements
        sift_in (H, num, i);  // of the first half of the array
                              // in inverse order (H[1] last)
    // 2nd: SORT
                       // The variable 'num' will be used now
    while (num > 1)    // as the size of the heap
    {
        tmp = H[num];       // Take the current max. from the
        H[num] = H[1];      // root of the heap to H[num]
        num --;
        H[1] = tmp;            // Reinsert the old
        sift_in (H, num, 1);   // H[num] into the heap
    }
}

void heapsort_floyd (sorteddatatype A[],   // Array to be sorted
                     uint32_t num)         // Size of the array
{
    sorteddatatype * H;
    sorteddatatype tmp;
    uint32_t i;          // NOTE: See the comments of the
                         //       previous function. This one
    if (num < 2)         //       is nearly identical. The only
        return;          //       difference is at the end

    H = A - 1;

    // 1st: HEAPIFY

    for (i=num>>1; i; i--)
        sift_in (H, num, i);

    // 2nd: SORT

    while (num > 1)
    {
        tmp = H[num];
        H[num] = H[1];
        num --;                       // Use optimized sift_in to
        sift_in_floyd (H, num, tmp);  // reinsert the old H[num]
    }                                 // into the heap
}

static inline void sift_in (
        sorteddatatype * H,     // Heap goes from H[1] to H[num]
        uint32_t         num,   // Current size of the heap
        uint32_t         i)     // Element to push down
{
    sorteddatatype tmp;   // Temporary var. for chained swaps
    uint32_t p, c;        // Pos. in the heap (parent and child)
    
    tmp = H[i];           // Save the value to push down
    p = i;                // This is the current parent
  
    for (c=p<<1; c<num; c<<=1)   // While it has two children
    {
        if (H[c] < H[c+1])       // Choose the child whith
            c ++;                // greater value

        if (H[c] <= tmp)         // If greater child is less/eq.
            break;               // to the initial value, stop
                                 // pushing down. Otherwise,
        H[p] = H[c];             // move the child up and
        p = c;                   // go down
    }
    
    if (c == num && H[c] > tmp)  // If there is a final "only
    {                            // child" greater than the
        H[p] = H[c];             // initial value, move the
        p = c;                   // child up and go down
    }
                          // Put the saved value in the hole
    H[p] = tmp;           // left by the last child moved up
}

static inline void sift_in_floyd (
        sorteddatatype * H,     // Heap goes from H[1] to H[num]
        uint32_t         num,   // Current size of the heap
        sorteddatatype   tmp)   // Value to be inserted
{                               // (Assume that H[1] is empty)

    uint32_t p, c;        // Pos. in the heap (parent and child)
  
    p = 1;
  
    for (c=p<<1; c<num; c<<=1)   // While it has two children
    {
        if (H[c] < H[c+1])       // Choose the one with the
            c ++;                // greater value

        H[p] = H[c];             // Move the child up and
        p = c;                   // go down
    }
  
    if (c == num)                // If there is a final "only
    {                            // child", move it up and
        H[p] = H[c];             // go down
        p = c;
    }                            // Note that this travel down
                                 // was done even if tmp had
    for (;;)                     // a great value
    {
        c = p;                      // Now, undo some of the
        p >>= 1;                    // previous steps if
                                    // necessary. This will
        if (p == 0 || H[p] >= tmp)  // happen very few times.
            break;                  // That's the key for the
                                    // optimization
        H[c] = H[p];
    }
   
    H[c] = tmp;         // Put the stored value in the hole
}

