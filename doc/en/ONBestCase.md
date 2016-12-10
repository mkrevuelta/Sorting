# About the claims of O(N) best-case time

<p align="right"><i>Esta página está en inglés. Si usted lo prefiere, puede leer la <a href="../es/ONBestCase.md">versión española</a></i></p>

From time to time, somebody argues that all sorting algorithms can take **O(N)** time in the best case. The chain of reasoning goes like this:

   + Before actually sorting, we can check whether the data are already sorted. This can be done in **O(N)** time.
   + Extend the sorting algorithm with this initial check. If the data are already sorted, then stop. Otherwise, execute the actual sorting algorithm.
   + The extended algorithm takes only **O(N)** time in the best case.

That is very nice, but I'm still interested in the real behaviour of the bare sorting algorithm. My reasons are:

   + I don't want the overhead of checking the order every time. If I call a function that sorts, that's probably because the data are not sorted.
   + The check doesn't provide any time saving when the data are _nearly_ sorted.

Indeed, the case of _nearly_ sorted data is very important. I will claim that a sorting algorithm is **O(N)** best case if:

   + It takes **O(N)** time for sorted data (without additional checks) **AND**
   + It takes _nearly_ **O(N)** time for _nearly_ sorted data.

This is a natural property of insertion sort and, to some extent, of bubble sort too. But these are **O(N<sup>2</sup>)** on average.

In the **O(N log N)** league, the usual best case time is also **O(N log N)**. This is the behaviour of quick sort, heap sort, shell sort, comb sort and the usual implementation of merge sort. The notable exceptions are smooth sort and _natural_ merge sort.

Precisely, smooth sort was named after this property. When the input changes from sorted to _nearly_ sorted, and then to less and less sorted, the execution time transitions _smoothly_ from **O(N)** to **O(N log N)**.

Heap sort is a special case. If it is implemented carefully and **without** Floyd's optimization, it takes **O(N)** time when all the input data are equal. The transition from **O(N)** to **O(N log N)** is smooth. That is, if _nearly all_ data are equal, it takes _nearly_ **O(N)**. Though, "equal data" is a specially restrictive case of "already sorted data". In this sense, heap sort is not comparable to smooth sort or _natural_ merge sort.


<br><br>
<a href='../LICENSE'><img src='../img/cc_by_88x31.png' alt='Creative Commons License' /></a><br>
**Author:** [Martín Knoblauch Revuelta](http://www.mkrevuelta.com/en/about-me/)<br>
This work is licensed under a [Creative Commons Attribution 3.0 Unported License](../LICENSE)</a>


