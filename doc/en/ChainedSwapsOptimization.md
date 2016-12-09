# Optimization of the chained swaps

The chained swaps optimization, also known as _floating hole_, is quite usual in some specific sorting algorithms. So much that it is hard to find them implemented without this optimization.

This optimization saves time by avoiding unnecessary assignments. For example, if we need to make three swaps in a row...

```C
    tmp = A[0];      // Swap A[0] with A[1]
    A[0] = A[1];
    A[1] = tmp;
    
    tmp = A[1];      // Swap A[1] with A[2]
    A[1] = A[2];
    A[2] = tmp;

    tmp = A[2];      // Swap A[2] with A[3]
    A[2] = A[3];
    A[3] = tmp;
```

... they can be chained as follows:

```C
    tmp = A[0];    // Save value of A[0] making a 'hole'
    A[0] = A[1];
    A[1] = A[2];   // Move values, shifting the 'hole' too
    A[2] = A[3];
    A[3] = tmp;    // Store in the 'hole' the value saved
```

On one hand, it is not fair to compare the performance of two algorithms when one uses this optimization and the other does not. On the other hand, we can not expect a big difference, since the usage of _caché_ memories reduces the benefits of this implementation.

This optimization is usually applied to the next sorting algorithms:

   + Insertion sort
   + Quick sort

It can also be applied to the next algorithms, but with a much more modest result:

   + Shell sort
   + Bubble sort
   + Comb sort
   + Heap sort
   + Smooth sort

<br><br>
<a href='../LICENSE'><img src='../img/cc_by_88x31.png' alt='Creative Commons License' /></a><br>
**Author:** [Martín Knoblauch Revuelta](http://www.mkrevuelta.com/en/about-me/)<br>
This work is licensed under a [Creative Commons Attribution 3.0 Unported License](../LICENSE)</a>

