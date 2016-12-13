# Optimización de los intercambios encadenados

<p align="right"><i>This page is in Spanish. If you prefer, you can read the <a href="../en/ChainedSwapsOptimization.md">English version</a></i></p>

La optimización de los intercambios encadenados, también conocida como el _hueco flotante_, es muy habitual en ciertos algoritmos de ordenación. Tanto que es difícil encontrar implementaciones de esos algoritmos que no hagan uso de ella.

Esta optimización consiste en evitar asignaciones innecesarias. Por ejemplo, si hay que realizar tres intercambios seguidos...

```C
    tmp = A[0];      // Intercambiar A[0] y A[1]
    A[0] = A[1];
    A[1] = tmp;
    
    tmp = A[1];      // Intercambiar A[1] y A[2]
    A[1] = A[2];
    A[2] = tmp;

    tmp = A[2];      // Intercambiar A[2] y A[3]
    A[2] = A[3];
    A[3] = tmp;
```

... se pueden encadenar como sigue:

```C
    tmp = A[0];    // Salvar valor de A[0] creando un 'hueco'
    A[0] = A[1];
    A[1] = A[2];   // Desplazar valores, moviendo el 'hueco'
    A[2] = A[3];
    A[3] = tmp;    // Guardar en el 'hueco' el valor salvado
```

Por un lado, no es justo comparar el rendimiento de dos algoritmos cuando uno de ellos la aplica y el otro no. Por otro lado, no cabe esperar una gran mejoría, ya que el uso de memorias _caché_ minimiza los beneficios de esta optimización.

Esta optimización se aplica habitualmente a los siguientes algoritmos de ordenación:

   + Inserción (_insertion sort_)
   + Rápido (_quick sort_)

Se puede aplicar también a los siguientes algoritmos, aunque con un resultado mucho más modesto:

   + Shell (_Shell sort_)
   + Burbuja (_bubble sort_)
   + CombSort (_comb sort_)
   + [Montículo (_heap sort_)](HeapSort.md)
   + [Suave (_smooth sort_)](SmoothSort.md)


<br><br>
<a href='../LICENSE'><img src='../img/cc_by_88x31.png' alt='Creative Commons License' /></a><br>
**Autor:** [Martín Knoblauch Revuelta](http://www.mkrevuelta.com/es/acerca-de-mi/)<br>
El contenido de esta página está bajo una [licencia de Creative Commons Reconocimiento 3.0 Unported](../LICENSE)</a>

