/*
    Copyright (c) 2013, Martin Knoblauch Revuelta
    See accompanying LICENSE
    
    ---------------------------------------------------------------
    smoothsort.c
    
    Implementation of Dijkstra's "smoothsort" algorithm. The
    heaps used in this algorithm have shapes like:
    
        O    __O      __O          ___O                  _____O
            / /      / /       ___/  /             _____/    /
           O O    __O O     __O   __O          ___O       __O
                 / /       / /   / /       ___/  /       / /
                O O     __O O   O O     __O   __O     __O O
                       / /             / /   / /     / /
                      O O           __O O   O O     O O
                                   / /
                                  O O
                                                (and so on)
    
    This code was derived from the wonderful explanation by
    Keith Schwarz, "Smoothsort Demystified" available at:
    
        http://www.keithschwarz.com/smoothsort/
        
    Indeed, Schwarz's web includes an implementation, and the
    one listed below is quite similar. It had to be, of course,
    since it was derived from a detailed description of the
    same algorithm. The main differences are:
    
        - This implementation is in plain old C, instead of C++
        
            * A simple typedef is used instead of templates
        
            * An uint64_t is used instead of a bit-vector
        
        - Many function calls and conditional branches are out
          of the loops for speed:
          
            * The functions heapify() and extract() are called
              once each. The loops that traverse the array are
              inside these functions
              
            * In heapify(), the list of heaps is constructed with
              a trivial heap of size L[1] _before_ entering the
              loop. Thus, the loop doesn't check for the corner
              case of an "empty list"
              
            * In extract(), the loop ends without extracting the
              final two elements. It's not necessary, since they
              form sorted heaps of trivial sizes L[1] and L[0].
              As before, this loop doesn't need to check for the
              corner case of an "empty list"
            
        - While moving values around, some assignments are saved
          with the trick of chained swaps
    ---------------------------------------------------------------
*/

#include "sorting.h"

static const uint32_t L[] =     // Leonardo numbers in [0,1<<32)
{
    1UL, 1UL, 3UL, 5UL, 9UL, 15UL, 25UL, 41UL, 67UL, 109UL, 177UL,
    287UL, 465UL, 753UL, 1219UL, 1973UL, 3193UL, 5167UL, 8361UL,
    13529UL, 21891UL, 35421UL, 57313UL, 92735UL, 150049UL,
    242785UL, 392835UL, 635621UL, 1028457UL, 1664079UL, 2692537UL,
    4356617UL, 7049155UL, 11405773UL, 18454929UL, 29860703UL,
    48315633UL, 78176337UL, 126491971UL, 204668309UL, 331160281UL,
    535828591UL, 866988873UL, 1402817465UL, 2269806339UL,
    3672623805UL
};

typedef struct
{
    uint64_t mask; // Leo. nums. in use (sizes of existing heaps)
    int offset;    // Add this to every bit's position ('mask'
}                  // always ends with a '1' bit, so 'offset' is
heapsizes;         // also the size of the smallest heap)

static heapsizes heapify (sorteddatatype A[], uint32_t num);

static void extract (sorteddatatype A[], uint32_t num,
                     heapsizes hsz);

void smoothsort (sorteddatatype A[], uint32_t num)
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

    hsz.mask = 1;             // Create a heap of size L[1]
    hsz.offset = 1;           // containing the first element

    for (i=1; i<num; i++)     // With every following element...
    {
        if (hsz.mask & 2)          // If possible (if contiguous
        {                                  // Leonardo numbers),
            hsz.mask = (hsz.mask>>2) | 1;  // fuse last two heaps
            hsz.offset += 2;
        }                          // Otherwise,
        else if (hsz.offset == 1)  // if last heap has size L[1]
        {
            hsz.mask = (hsz.mask << 1) | 1;  // the new is L[0]
            hsz.offset = 0;
        }
        else                       // Otherwise, new heap L[1]
        {
            hsz.mask = (hsz.mask << (hsz.offset-1)) | 1;
            hsz.offset = 1;
        }
        
            // The current heap will be fused in the future if:
            //
            //     a) The sizes of this heap and the previous are
            //        contiguous Leonardo numbers AND there is at
            //        least one more element in the array
            //  OR
            //     b) This heap has size L[x] where x>0 AND there
            //        is still space for a heap of size L[x-1] and
            //        one more element (L[x]+L[x-1]+1 --> L[x+1])

        wbf = ( (hsz.mask & 2) &&
                i+1 < num                 ) ||
              ( hsz.offset > 0    &&
                1ULL+i+L[hsz.offset-1] < num );

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
    for (i=num-1; i>1; i--)  // When only two remain, it's done
    {
        if (hsz.offset<2)         // If last heap has size L[1] or
        {                         // L[0] (both ==1), just remove
            do                    // this heap (update the
            {                     // heapsizes struct) leaving the
                hsz.mask >>= 1;   // single element untouched
                hsz.offset ++;
            }                       // The mask will never be 0
            while (!(hsz.mask&1));  // because the loop terminates
        }                           // early (with two heaps of
        else                        // sizes L[1] and L[0])
        {
            ch[1] = i - 1;                   // Position of right
            ch[0] = ch[1] - L[hsz.offset-2]; // and left children

            hsz.mask &= ~1ULL;       // Remove current heap

            for (j=0; j<2; j++)      // For every child heap (left
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
    sorteddatatype * left, * right; // Pos. of children heaps
    sorteddatatype * next;          // Chosen child (greater root)
    sorteddatatype tmp;             // Value to move down
    int nsz;                        // Size of chosen child heap
    
    if (size < 2)        // If we are in a leaf,
        return;          // there's nothing to do

    tmp = *root;         // Backup the initial value
    
    do                        // While there are children heaps...
    {
        right = root - 1;           // Locate children
        left = right - L[size-2];
        
        if (*right < *left)         // Compare their roots
        {
            next = left;            // Choose left child heap
            nsz = size - 1;         // (larger subheap)
        }
        else
        {
            next = right;           // Choose right child heap
            nsz = size - 2;         // (smaller subheap)
        }
                                    // If both roots are less than
        if (*next <= tmp)           // the initial root, we have
            break;                  // reached its final position

        *root = *next;              // Otherwise, push up the
                                    // greater root and
        root = next;                // proceed down to the
        size = nsz;                 // next level
    }
    while (size > 1);          // If we reach a leaf, stop
    
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
        
        if (hsz.offset > 1)           // If this heap has children
        {
            right = root - 1;                 // Locate children
            left = right - L[hsz.offset-2];
            
            if (max < *left)                  // Use the maximum
                max = *left;                  // value for the
                                              // comparison below,
            if (max < *right)                 // since it is the
                max = *right;                 // effective root
        }                                     // of this heap
        
        next = root - L[hsz.offset];  // Position of next heap

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

