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

### Constant time: O(1)

We'll say that an algorithm takes **O(1)** time when its execution time does not depend on **N** (the size of the problem). For example:

```C
double central_element (const double A[],        // Array of numbers
                        unsigned num)            // Size of the array
{
    return A[num/2];                    // Return the value located
}                                       // in the central position
```
The function `central_element()` will always take the same time to execute, no matter what the size of the array is.

The next function also takes **O(1)** time:

```C
double random_sum (const double A[],             // Array of numbers
                   unsigned num)                 // Size of the array
{
    unsigned i;
    double sum;                      // Add 327 elements of the array
                                     // chosen at random (might sum
    for (i=0, sum=0; i<327; i++)     // the same element several
        sum += A[rand()%num];        // times)
        
    return sum;
}
```

It takes much more time than the previous function, but we must consider it **O(1)** because it's a constant amount of time. It does not depend on whether the array has three elements or three millions.

If we compare them, we will say that they both take **O(1)** time, but the constant factor is quite higher in `random_sum()` than in `central_element()`.

### Logarithmic time: O(log N)

The next function adds the elements of some specific positions of an array:

```C
double sum_powers_3 (const double A[],           // Array of numbers
                     unsigned num)               // Size of the array
{
    unsigned i;
    double sum;
                                     // Add the elements of the array
    for (i=1, sum=0; i<num; i*=3)    // whose index is a power of 3
        sum += A[i];                 // (including position 1)
        
    return sum;
}
```

Note that the condition to stay in the loop is `i<num`, but the variable `i` is not incremented by one unit in each iteration, but multiplied by 3. The condition of the loop gets to be false when **3<sup>x</sup> ≥ N**, where **x** is the number of iterations and **N** is the value of `num`. Working out the value of **x**, we get to **x ≈ log<sub>3</sub>N**.

The base of the logarithm is irrelevant since the logarithms of a same number in different bases keep a fixed proportion. That is, **log<sub>a</sub>N = k×log<sub>b</sub>N**, where **k** is constant (specifically,**k = log<sub>a</sub>b**).

The next function also takes **O(log N)**:

```C
unsigned count_ones (unsigned n)      // Count the number of ones in
{                                     // n's binary representation
    unsigned ones;
    
    for (ones=0; n; n>>=1)        // While n!=0, add to 'ones'
        ones += n & 1;            // the lowest bit of 'n', and
                                  // shift 'n' one bit to the
    return ones;                  // right
}
```

In nowadays' computers, the type `unsigned` usually has 32 bits. This imposes a reasonably low limit to the number of iterations that the two previous functions will execute. For this reason they are considered **O(1)** in some contexts. Technically they are not, but they both are faster than the function `random_sum()` seen earlier.

As a conclusion, when it comes to compare **O(1)** algorithms with **O(log N)** algorithms, we have to take into account the constant factors.

### Linear time: O(N)

The next function takes **O(N)** time:

```C
double mean (const double A[],                   // Array of numbers
             unsigned num)                       // Size of the array
{
    unsigned i;
    double sum;
                                        // Add all the elements of
    for (i=0, sum=0; i<num; i++)        // the array to compute the
        sum += A[i];                    // arithmetic mean
        
    return num ? sum/num : 0;           // If num==0, avoid division
}                                       // (by zero) and return 0
```

It's not so obvious in the next case, but it also takes **O(N)** time. Whatever the function does to the data of the array is irrelevant. Watch carefully the relationship between the two loops:

```C
void faa (double A[],                            // Array of numbers
          unsigned num)                          // Size of the array
{
    unsigned i, j;
    
    for (i=0; i<num; i++)
        for (j=i; j<num && A[j]!=3; j++)   // WATCH OUT: Changing num
            A[--num] *= 2;                 //   <--- here affects the
}                                          //           external loop
```

### Linear-logarithmic (_linearithmic_) time: O(N log N)

The next function contains two nested loops:

```C
unsigned fee (const double A[],                  // Array of numbers
              unsigned num)                      // Size of the array
{
    unsigned i, c, m;
    
    for (c=0, m=num; m; m>>=1)           //   log(N) iterations *
        for (i=0; i<num; i++)            //        N iterations   =
            if (i!=m-1 && A[i]==A[m-1])  // N*log(N) iterations
                c ++;

    return c;
}
```

The external loop will execute log<sub>2</sub>(`num`) iterations. In each one of them, the internal loop will execute `num` iterations. Therefore, the total number of times that the `if` sentence is executed must be `num`×log<sub>2</sub>(`num`).

### Quadratic time: O(N<sup>2</sup>)

The next function contains two nested loops. Both make `num` iterations each time, so the total number of iterations of the inner loop will be `num`<sup>2</sup>.

```C
unsigned fii (const double A[],                  // Array of numbers
              unsigned num)                      // Size of the array
{
    unsigned i, j, c;
    
    for (i=c=0; i<num; i++)              //   N iterations *
        for (j=0; j<num; j++)            //   N iterations   =
            if (i<j && A[i]>A[j])        // N*N iterations
                c ++;

    return c;
}
```

The next function is an optimized version of the previous one. Note that the comparison `i<j` has been removed and, in the inner loop, the initial value of `j` has been changed. It will return the same result as `fii()`, but in half the time. Though, it's still **O(N<sup>2</sup>)** because the only thing that has changed is the constant factor:

```C
unsigned foo (const double A[],                  // Array of numbers
              unsigned num)                      // Size of the array
{
    unsigned i, j, c;
    
    for (i=c=0; i<num; i++)    
        for (j=i+1; j<num; j++)          // (N-1)+(N-2)+...+(1) =
            if (A[i]>A[j])               // N*N/2 iterations (approx)
                c ++;

    return c;
}
```

### Polynomial time: O(N<sup>3</sup>), O(N<sup>4</sup>)...

**O(N<sup>3</sup>):**

```C
    for (i=0; i<num; i++)
        for (j=0; j<num; j++)
            for (k=0; k<num; k++)
                // ... do something O(1) here ...
```

**O(N<sup>4</sup>)**:

```C
    for (i=0; i<num; i++)
        for (j=0; j<num; j++)
            for (k=0; k<num; k++)
                for (m=0; m<num; m++)
                    // ... do something O(1) here ...
```

... and so on.

Note: in a strict sense, **O(1)**, **O(N)** and **O(N<sup>2</sup>)** are also _polynomial_ complexities, because **1**, **N** and **N<sup>2</sup>** are polynomials (of degrees 0, 1 and 2 respectively).

### Other complexities: O(N!)...

Obviously we need to avoid, insofar as possible, absurdly slow algorithms as the one described at the beginning of this page. However, there are some problems for which there is no known algorithm that ends in polynomial time, like the [Travelling Salesman Problem](http://en.wikipedia.org/wiki/Travelling_salesman_problem) or the [Knapsack Problem](http://en.wikipedia.org/wiki/Knapsack_problem).

## Space

The "big O" notation is also useful for describing the amount of additional memory that an algorithm needs depending on the size of the problem. We specify _additional_ to remark that we are not including the space occupied by the input or output data.

If a function declares only a few variables of primitive types (`int`, `float`, etc.) or arrays of fixed size, it is considered to only require **O(1)** additional space. If it uses an array of size **N**, it is considered to require **O(N)** additional space, and so on.

## Beware of recursion

The next function computes the factorial of a number in **O(N)** time and using **O(1)** additional space:

```C
double factorial_iter (unsigned n)
{
    double f;
    
    for (f=1; n>1; n--)
        f *= n;
        
    return f;
}
```

The next one computes the same, but using recursion:

```C
double factorial_rec (unsigned n)
{
    return n<=1 ? 1                       // If n<=1, end
                : n * factorial_rec(n-1); // Otherwise, make
}                                         // recursive call
```

The recursive version takes **O(N)** time too, but it is considerably slower. The constant factor is higher because a function call takes much more time than a loop iteration.

Furthermore, as it makes `n-1` nested recursive calls, it uses **O(N)** additional space. Each call uses some memory to _remember_ where to continue after the return, to store the parameter `n` (there's a different `n` per call) and to deliver the value returned by the function.

Let's see another example of what not to do:

```C
unsigned fibonacci (unsigned n)       // Fibonacci numbers:
{                                     // 0, 1, 1, 2, 3, 5, 8, 13, ...
    return n==0 ? 0 :
           n==1 ? 1 :                 // Except for the two first,
                  fibonacci(n-1) +    // every number is the sum
                  fibonacci(n-2);     // of the two previous
}
```

In this case the execution time grows wildly towards **O(2<sup>N</sup>)**. The number of calls is not exactly **2<sup>N</sup>**, but it is somewhere between **2<sup>N</sup>** and **2<sup>N/2</sup>**. Practically, the difference is irrelevant: it is an absurdly slow function. It is specially absurd because it computes the same numbers many times.

The additional space required is _only_ **O(N)** because the longest sequence of nested recursive calls is proportional to **N**.

The next function computes the same in **O(N)** time and using just **O(1)** additional space:

```C
unsigned fibonacci_iter (unsigned n)  // Fibonacci numbers:
{                                     // 0, 1, 1, 2, 3, 5, 8, 13, ...
    unsigned a, b, tmp;
    
    if (n<2)
        return n;
        
    for (a=b=1; n>2; n--)
    {
        tmp = a + b;
        a = b;
        b = tmp;
    }
    
    return b;
}
```

## More information

For more information on the exact meaning of **O**, **Θ**, **Ω** and **ω**, see:

  + [Big O notation - Related asymptotic notations](http://en.wikipedia.org/wiki/Big_O_notation#Related_asymptotic_notations)


<br><br>
<a href='../LICENSE'><img src='../img/cc_by_88x31.png' alt='Creative Commons License' /></a><br>
**Author:** [Martín Knoblauch Revuelta](http://www.mkrevuelta.com/en/about-me/)<br>
This work is licensed under a [Creative Commons Attribution 3.0 Unported License](../LICENSE)</a>
