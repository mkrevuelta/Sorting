/*
    Copyright (c) 2013, Martin Knoblauch Revuelta
    See accompanying LICENSE
    
    ---------------------------------------------------------------
    smoothsort_fib_1.c
    
    Implementation of a varaition of Dijkstra's "smoothsort"
    algorithm. This version is similar to the one in smoothsort.c
    but with heaps of a slightly different shape:
    
        O     O      __O        __O             _____O
             /     _/ /       _/ /          ___/    /
            O     O  O     __O  O        __O     __O
                 /       _/ /  /       _/ /    _/ /
                O       O  O  O     __O  O    O  O
                       /          _/ /  /    /
                      O          O  O  O    O
                                /                 (and so on)
                               O

    In the original smoothsort the smallest heaps have three
    elements. This version is more impatient, and builds them
    as soon as a second element is present.

    The sizes of the heaps follow a similar formula, but starting
    with { 1, 2 } instead of { 1, 1 }. They coincide with the
    nonzero Fibonacci-minus-1 numbers, hence the name
    "smoothsort_fib_1()".

    The code gets simpler at some points but longer at others.
    Now there are parent elements with just one child.

    Dijkstra himself commented the possibility of this variation
    in his EWD796a:
    
           "Remark 2. We can now partly justify our choice of
            the Leonardo numbers as available stretch lengths,
            i.e. justify why we have not chosen (with the same
            recurrence relation)
 
              ....   33   20   12   7   4   2   1   (0)   .

            The occurrence of length 2 would have required a
            sift able to deal with fathers having one or two
            sons, like the sift required in heapsort ; thanks
            to the Leonardo numbers a father has always two
            sons and, consequently, smoothsort's sift is
            simpler. (End of Remark 2.)"
    ---------------------------------------------------------------
*/

#include "sorting.h"
                                 // Nonzero Fibonacci-1 numbers
static const uint32_t E[] =      // in the range [1,1<<32)
{
    1UL, 2UL, 4UL, 7UL, 12UL, 20UL, 33UL, 54UL, 88UL, 143UL,
    232UL, 376UL, 609UL, 986UL, 1596UL, 2583UL, 4180UL, 6764UL,
    10945UL, 17710UL, 28656UL, 46367UL, 75024UL, 121392UL,
    196417UL, 317810UL, 514228UL, 832039UL, 1346268UL, 2178308UL,
    3524577UL, 5702886UL, 9227464UL, 14930351UL, 24157816UL,
    39088168UL, 63245985UL, 102334154UL, 165580140UL, 267914295UL,
    433494436UL, 701408732UL, 1134903169UL, 1836311902UL,
    2971215072UL
};

typedef struct
{
    uint64_t mask; // Fib-1 nums. in use (sizes of existing heaps)
    int offset;    // Add this to every bit's position ('mask'
}                  // always ends with a '1' bit, so 'offset' is
heapsizes;         // also the size of the smallest heap)

static heapsizes heapify (sorteddatatype A[], uint32_t num);

static void extract (sorteddatatype A[], uint32_t num,
                     heapsizes hsz);

void smoothsort_fib_1 (sorteddatatype A[], uint32_t num)
{
    heapsizes hsz;
 
    if (num < 2)  // If there's only one element, it's done.
        return;   // The other functions assume 2 or more elements

    hsz = heapify (A, num);   // Build the ordered list of heaps

    extract (A, num, hsz);    // Consume the list of heaps
}

static inline void sift_in (sorteddatatype * root, int size);

static inline void interheap_sift (sorteddatatype * root,
                                   heapsizes hsz);

static heapsizes heapify (sorteddatatype A[], uint32_t num)
{
    heapsizes hsz;       // 'List' of sizes of existing heaps
    
    uint32_t i;          // Loop index for traversing the array
    
    int wbf;             // Flag indicating whether a newly
                         // created heap will be fused later in a
                         // larger heap (wbf!=0) or not (wbf==0)
    
    hsz.mask = 1;        // Create a heap of size E[0]
    hsz.offset = 0;      // containing the first element

    for (i=1; i<num; i++)     // With every following element...
    {
        if (hsz.mask & 2)          // If possible (if contiguous
        {                                  // Fib.-1 numbers),
            hsz.mask = (hsz.mask>>2) | 1;  // fuse last two heaps
            hsz.offset += 2;
        }                          // Otherwise,
        else if (hsz.offset == 0)  // if last heap has size E[0]
        {
            hsz.mask = (hsz.mask>>1) | 1;  // Make it of size E[1]
            hsz.offset = 1;
        }
        else       // Otherwise, just append a heap of size E[0]
        {
            hsz.mask = (hsz.mask << hsz.offset) | 1;
            hsz.offset = 0;
        }
        
            // The current heap will be fused in the future if:
            //
            //     a) The sizes of this heap and the previous are
            //        contiguous Fib-1 numbers AND there is at
            //        least one more element in the array
            //  OR
            //     b) This heap has size E[x] where x>0 AND there
            //        is still space for a heap of size E[x-1] and
            //        one more element (E[x]+E[x-1]+1 --> E[x+1])

        wbf = ( (hsz.mask & 2) &&
                i+1 < num                 ) ||
              ( hsz.offset > 0    &&
                1ULL+i+E[hsz.offset-1] < num );

        if (wbf)                       // If this new heap will be
            sift_in (A+i, hsz.offset); // fused, don't propagate
        else                           // the root (just fix this
            interheap_sift (A+i, hsz); // heap). If it will _not_
    }                                  // be fused, propagate the
                                       // root through the
    return hsz;                        // sequence of heaps to
}                                      // ensure correct ordering

static void extract (sorteddatatype A[], uint32_t num,
                     heapsizes hsz)
{
    uint32_t i;          // Loop index for traversing the array

    uint32_t ch[2];      // Position of left and right children
                         // of a newly created heap
    int j;
                             // Extract elems. starting at the end
    for (i=num-1; i>2; i--)  // When only three remain, it's done
    {
        if (hsz.offset == 0)      // If last heap has size E[0]
        {                         // just remove this heap (update
            do                    // the heapsizes struct) leaving
            {                     // the single element untouched
                hsz.mask >>= 1;
                hsz.offset ++;      // The mask will never be 0
            }                       // because the loop terminates
            while (!(hsz.mask&1));  // early with a heap of size 1
        }
        else
        {
            ch[j=1] = i - 1;                  // Position of right
                                              // and left child
            if (hsz.offset > 1)                     // (if any)
                ch[j=0] = ch[1] - E[hsz.offset-2];

            hsz.mask &= ~1ULL;       // Remove current heap

            for (; j<2; j++)         // For every child heap (left
            {                                            // first)
                hsz.mask = (hsz.mask << 1) | 1;
                hsz.offset --;                  // Add heap to the
                                                // list and ensure
                interheap_sift (A+ch[j], hsz);  // ordering of
            }                                   // roots
        }        
    }
}

static inline void sift_in (sorteddatatype * root, int size)
{
    sorteddatatype * left;          // Position of left child heap
    sorteddatatype * next;          // Chosen child (greater root)
    sorteddatatype tmp;             // Value to move down
    int nsz;                        // Size of chosen child heap
    
    if (size < 1)        // If we are in a leaf,
        return;          // there's nothing to do

    tmp = *root;         // Backup the initial value
    
    do                        // While there are children heaps...
    {
        next = root - 1;               // Choose temporarily the
        nsz = size==1 ? 0 : size-2;    // right (or "only") child

        if (size > 1)                  // If there is a left child
        {
            left = root - 1 - E[size-2];  // Locate it and compare
                                          // its root with the one
            if (*next < *left)            // of the other child
            {
                next = left;           // Choose left child heap
                nsz = size - 1;        // (larger subheap)
            }
        }
                                    // If both roots are less than
        if (*next <= tmp)           // the initial root, we have
            break;                  // reached its final position

        *root = *next;              // Otherwise, push up the
                                    // greater root and
        root = next;                // proceed down to the
        size = nsz;                 // next level
    }
    while (size > 0);          // If we reach a leaf, stop
    
    *root = tmp;         // Write the initial value in its
}                        // final position

static inline void interheap_sift (sorteddatatype * root,
                                   heapsizes hsz)
{
    sorteddatatype * next;   // Pos. of (root of) next heap
    sorteddatatype * left;   // Pos. of left child of current heap
    sorteddatatype * right;  //  "   "  right  "   "     "     "
    sorteddatatype tmp;      // Value to move left
    sorteddatatype max;      // Effective root value of curr. heap

    tmp = *root;      // Backup the initial value
    
    while (hsz.mask != 1)  // Traverse the list of heaps
    {                      // from right to left
        max = tmp;
        
        if (hsz.offset > 0)       // If this heap has children
        {
            right = root - 1;         // Locate it and check its
                                      // value
            if (max < *right)
                max = *right;
                
            if (hsz.offset > 1)   // If it has _two_ children
            {
                left = right - E[hsz.offset-2];
            
                if (max < *left)      // Locate it and check its
                    max = *left;      // value too. The maximum is
            }                         // the effective root of
        }                             // this heap
        
        next = root - E[hsz.offset];  // Position of next heap

        if (*next <= max)             // If the ordeing is OK,
            break;                    // stop here

        *root = *next;                // Otherwise, push up the
        root = next;                  // root of that heap and
                                      // go there
        do
        {                             // Extract the previous
            hsz.mask >>= 1;           // heap from the list (note
            hsz.offset ++;            // that 'hsz' is just a
        }                             // temporary copy)
        while (!(hsz.mask&1));
    }
                                      // Put the initial root in
    *root = tmp;                      // the heap where we stopped
    sift_in (root, hsz.offset);       // and ensure the correct
}                                     // internal ordering in it

