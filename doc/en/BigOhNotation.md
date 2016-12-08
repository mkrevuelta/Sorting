# Computational complexity and the "Big O" notation

<p align="right"><i>Esta página está en inglés. Si usted lo prefiere, puede leer la <a href="../es/BigOhNotation.md">versión española</a></i></p>

## Introduction

The [computational complexity](http://en.wikipedia.org/wiki/Computational_complexity_theory) of an algorithm is a measure of the time and space (in memory) required for its execution, depending on the size of the problem.

The ["Big O" notation](http://en.wikipedia.org/wiki/Big_O_notation) is used for describing the behaviour of these two parameters (time and space) when the size of the problem changes.

The documentation of this project uses the "Big O" notation to describe and compare the different sorting algorithms. This page provides the informal background required to understand this notation.

## An illustrative example

Let's say that we have three cities **A**, **B** and **C**. We want to sort them in ascending order of population. We might try to sort them using the next algorithm:

  + Try every one of the 6 possible permutations (**ABC**, **ACB**, **BAC**, **BCA**, **CAB** y **CBA**). With every one:
    - Traverse the chosen permutation **xyz** comparing the population of every city with that of the next one. If the population of **x** is less than the population of **y**, and that of **y** is less than the population of **z**, we have finished.

Since there are only six possible permutations, this algorithm will sort the three cities in a very short time. We can't say that it takes a blink of an eye because a blink of an eye is an eternity in comparison.

Though, how would behave this algorithm if we increased the number of cities?

If we add a fourth city **D**, the number of permutations is multiplied by four, since we can insert the **D** in four different positions of every permutation of the three cities: **xyzD**, **xyDz**, **xDyz**, and **Dxyz**. In total we have twenty four possible permutations: **ABCD**, **ABDC**, **ADBC**, **DABC**; **ACBD**, **ACDB**, **ADCB**, **DACB**; **BACD**... and so on.

If we add a fifth city **E**, these twenty four permutations get multiplied by five, throwing a total of one hundred and twenty. It's still far less time than a blink of an eye, but this growth is a bad sign. In addition, analysing every permutation costs now four comparisons, while it did cost only two with three cities. The total will be up to 480 comparisons while it was only 12 for three cities. Sorting five cities requires forty times more time than sorting three!

In general, with **N** cities we have **N×(N-1)×(N-2)×...×1** permutations, that is, **N!** (**N** "factorial"). With 62 cities we have 62! = 31469973260387937525653122354950764088012280797258232192163168247821107200000000000000 permutations. This number is so huge that we'll express it in scientific notation: 62! ≈ 3'15×10<sup>85</sup>. This amount is greater than the estimated number of particles contained in the whole observable universe!

It should be clear by now that this algorithm is insanely slow. So slow that it isn't even practical for sorting a few dozens of elements. A good programmer must be trained to reach this conclusion at first sight, without needing to implement and execute the algorithm.

## Time

The previous algorithm makes up to **N!×(N-1)** comparisons in order to sort **N** cities. It also needs to execute other small operations, but the total number will be proportional to **N!×(N-1)** in any case. If it needs in addition some fixed amount of time at the beginning or at the end, we will ignore them. We will also disregard any constant factor that multiplies the total time. We are not interested in computing the exact time for any specific **N**. We are interested in the long term evolution as **N** grows. Therefore, we will simply say that it requires a maximum time proportional to **N!×(N-1)**.

It's worth to mention that the previous algorithm would make only **N-1** comparisons in the best case, that is, when the first permutation evaluated happened to be the desired ordering.

We will also analyse the average case. In the previous algorithm, supposing that every permutation has the same probability of being the desired ordering, the average case will require half the time of the worst case. Since this is a constant factor, we will disregard it. We will consider that the execution time of the average case and the execution time of the worst case belong in the same category.

**To be continued...**


<br><br>
<a href='../LICENSE'><img src='../img/cc_by_88x31.png' alt='Creative Commons License' /></a><br>
**Author:** [Martín Knoblauch Revuelta](http://www.mkrevuelta.com/en/about-me/)<br>
This work is licensed under a [Creative Commons Attribution 3.0 Unported License](../LICENSE)</a>

