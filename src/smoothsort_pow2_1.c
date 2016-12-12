/*
    Copyright (c) 2013, Martin Knoblauch Revuelta
    See accompanying LICENSE.TXT
    
    ---------------------------------------------------------------
    smoothsort_pow2_1.c
    
    Implementation of a varaition of Dijkstra's "smoothsort"
    algorithm. This version is similar to the one in smoothsort.c
    but with heaps of a slightly different shape:
    
        O    __O         ___O                    _______O
            / /      ___/  /             _______/      /
           O O    __O   __O          ___O          ___O
                 / /   / /       ___/  /       ___/  /
                O O   O O     __O   __O     __O   __O
                             / /   / /     / /   / /
                            O O   O O     O O   O O
                                                     (and so on)
                                

    In the original smoothsort the heaps are not perfectly
    balanced, becuse every heap is built with child heaps of
    different size. In this version, the heaps are perfectly
    balanced.

    As a result, the constraints are slightly different. Heaps
    of consecutive sizes are now allowed anywhere. Two heaps of
    equal size are allowed at the end of the list. In the code
    that follows, this circumstance is indicated by the flag
    called 'bis' in the 'heapsizes' structure.

    Dijkstra himself commented the possibility of this variation
    in his EWD796:
    
           "One can also raise the question why I have chosen
            Leonardo numbers for my stretch lengths: ... 63 31
            15 7 3 1 is also a possibility, which seems
            attractive since each stretch can now be viewed as
            the postorder traversal of a completely balanced
            tree. I know why I chose the Leonardo numbers: with
            the balanced binary trees the average number of
            stretches is 1.2559
            (= (1/4)·(5+sqrt(5))·(log2(1+sqrt(5))-1) times the
            average number of stretches with the Leonardo
            numbers. (I do not present this ratio as a
            compelling argument.)"

    The sizes of the heaps are powers of two minus one, hence the
    name "smoothsort_pow2_1()".
    
    NOTE: In the code below I assume that bitshift operations
          take O(1) time, no matter how big is the shift. If this
          is not your case, consider using an additional field
          in the 'heapsizes' structure, and maintain that field
          equal to 1<<offset.
    ---------------------------------------------------------------
*/

#include "sorting.h"

typedef struct
{
    uint32_t mask; // Heap sizes in use (sizes of existing heaps)
    
                   // Add this to every bit's position ('mask'
    short offset;  // always ends with a '1' bit, so 'offset' is
                   // also the size of the smallest heap)
                   
    char bis;      // 1="There is another heap of size 'offset'"
}
heapsizes;

static heapsizes heapify (sorteddatatype A[], uint32_t num);

static void extract (sorteddatatype A[], uint32_t num,
                     heapsizes hsz);

void smoothsort_pow2_1 (sorteddatatype A[], uint32_t num)
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
    
    hsz.mask = 1;        // Create a heap of size 0
    hsz.offset = 0;      // containing the first element
    hsz.bis = 0;

    for (i=1; i<num; i++)     // With every following element...
    {
        if (hsz.bis)          // If possible (contiguous heaps
        {                                  // of same size),
            hsz.bis  = (hsz.mask>>1) & 1;  // fuse last two heaps
            hsz.mask = (hsz.mask>>1) | 1;
            hsz.offset ++;
        }                          // Otherwise,
        else if (hsz.offset == 0)  // if last heap has size 0
        {
            hsz.bis = 1;           // Make another (the 'bis')
        }
        else       // Otherwise, just append a heap of size 0
        {
            hsz.mask = (hsz.mask << hsz.offset) | 1;
            hsz.offset = 0;
        }
        
            // The current heap will be fused in the future if:
            //
            //     a) The sizes of this heap and the previous are
            //        equal AND there is at least one more element
            //        in the array
            //  OR
            //     b) There is still space in the array for
            //        another heap of the same size plus one more
            //        element

        wbf = hsz.bis ? i+1 < num                   :
                        i+(2ULL<<hsz.offset) < num;

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
        if (hsz.offset == 0)      // If last heap has size 0
        {                         // just remove this heap (update
            if (hsz.bis)          // the heapsizes struct) leaving
                hsz.bis = 0;      // the single element untouched
            else
                do
                {
                    hsz.mask >>= 1;     // The mask will never be
                    hsz.offset ++;      // 0 because the loop
                }                       // terminates early with
                while (!(hsz.mask&1));  // two heaps of size 0
        }
        else
        {
            ch[1] = i - 1;                   // Position of right
            ch[0] = i - (1UL<<hsz.offset);   // and left children

            if (!hsz.bis)
                hsz.mask &= ~1UL;

            hsz.mask = (hsz.mask << 1) | 1;
            hsz.offset --;
                           // Convert current heap in two  smaller
                           // heaps but pretend temporarily that
            hsz.bis = 0;   // there is only one

            for (j=0; j<2; j++)      // For every child heap (left
            {                                            // first)
                                                // Ensure
                interheap_sift (A+ch[j], hsz);  // ordering of
                                                // roots
                                                
                hsz.bis = 1;  // Stop pretending. There are _two_
            }                 // heaps of the same size
        }        
    }
}

static inline void sift_in (sorteddatatype * root, int size)
{
    sorteddatatype * left;          // Position of left child heap
    sorteddatatype * next;          // Chosen child (greater root)
    sorteddatatype tmp;             // Value to move down

    if (size < 1)        // If we are in a leaf,
        return;          // there's nothing to do

    tmp = *root;         // Backup the initial value
    
    do                        // While there are children heaps...
    {
        next = root - 1;      // Choose temporarily the right ch.

        left = root - (1UL<<size);  // Locate the left child,
                                    // compare the roots and
        if (*next < *left)          // choose the greater
            next = left;
                                    // If both roots are less than
        if (*next <= tmp)           // the initial root, we have
            break;                  // reached its final position

        *root = *next;              // Otherwise, push up the
                                    // greater root and
        root = next;                // proceed down to the
        size --;                    // next level
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
    
    while (hsz.bis || hsz.mask != 1)  // Traverse the list of
    {                                 // heaps from right to left
        max = tmp;
        
        if (hsz.offset > 0)     // If this heap has children
        {
            right = root - 1;     // Locate and check them.
                                  // The max. of the propagated
            if (max < *right)     // value and the children is
                max = *right;     // the effective root of the
                                                // current heap
            left = root - (1UL<<hsz.offset);

            if (max < *left)
                max = *left;
        }

        next = root + 1 - (2UL<<hsz.offset);  // Pos. of next heap

        if (*next <= max)             // If the ordeing is OK,
            break;                    // stop here

        *root = *next;                // Otherwise, push up the
        root = next;                  // root of that heap and
                                      // go there
        if (hsz.bis)
            hsz.bis = 0;
        else                          // Extract the previous
            do                        // heap from the list (note
            {                         // that 'hsz' is just a
                hsz.mask >>= 1;       // temporary copy)
                hsz.offset ++;
            }
            while (!(hsz.mask&1));
    }
                                      // Put the initial root in
    *root = tmp;                      // the heap where we stopped
    sift_in (root, hsz.offset);       // and ensure the correct
}                                     // internal ordering in it

