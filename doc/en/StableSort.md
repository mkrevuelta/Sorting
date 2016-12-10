# Explanation of the term "stable sort"

<p align="right"><i>Esta página está en inglés. Si usted lo prefiere, puede leer la <a href="../es/StableSort.md">versión española</a></i></p>

While teaching sorting algorithms, people generally use numbers. The most usual is to sort in ascending order. Sometimes they introduce the small sophistication of sorting in descending order. However, if two numbers are equals, using one or another doesn't make any difference.

Though, things are a bit more complicated in real life. I can sort my books according to many different criteria:

   + By title in alphabetic order
   + By author in alphabetic order...
      - ...of first name, last name
      - ...of last name, first name
   + By year of edition
   + By genre (novel, tale, fairy tale, essay, treaty, technical manual, guide book...)

Let's imagine that my books are already sorted by title in alphabetic order. Now I sort them by year of edition in ascending order. In one end will be the oldest and in the opposite end the newest. Those of year 2000, for instance, will be all together.

But within the group of books of year 2000, in which order are they now? If I used a **stable** sorting algorithm, the books of year 2000 are together and sorted by title in alphabetic order. If I used a **non stable** sorting algorithm, the books of year 2000 are together, but shuffled (in any random order with respect to each other).

The key is that stable sorting algorithms preserve the relative ordering of the elements considered _equal_ by the sorting criteria in use.

The next algorithms perform a stable sort:

   + Insertion sort
   + Bubble sort
   + Merge sort

The next algorithms perform a **non** stable sort:

   + Selection sort
   + Quick sort
   + Heap sort
   + Shell sort
   + Comb sort
   + Smooth sort

The only algorithm of the **O(N log N)** time category (see ["big Oh" notation](BigOhNotation.md)) that performs a stable sort is merge sort. The main drawback (and probably the only one) of this algorithm is that it requires **O(N)** additional space. Interestingly, any sorting algorithm can be modified to make a stable sort by using **O(N)** additional space.


<br><br>
<a href='../LICENSE'><img src='../img/cc_by_88x31.png' alt='Creative Commons License' /></a><br>
**Author:** [Martín Knoblauch Revuelta](http://www.mkrevuelta.com/en/about-me/)<br>
This work is licensed under a [Creative Commons Attribution 3.0 Unported License](../LICENSE)</a>

