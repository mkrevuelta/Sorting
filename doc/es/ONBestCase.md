# Acerca de las alegaciones de tiempos O(N) en el mejor caso

<p align="right"><i>This page is in Spanish. If you prefer, you can read the <a href="../en/ONBestCase.md">English version</a></i></p>

De vez en cuando, alguien argumenta que todos los algoritmos de ordenación pueden tardar **O(N)** en el mejor caso. La cadena de razonamiento es más o menos como sigue:

   + Antes de ordenar realmente, podemos comprobar si los datos ya están ordenados. Esto se puede hacer en tiempo **O(N)**.
   + Ampliar el algoritmo de ordenación con esta comprobación inicial. Si los datos ya están ordenados, parar. En caso contrario, ejecutar el verdadero algoritmo de ordenación.
   + El algoritmo ampliado tarda sólo **O(N)** en el mejor caso.

Eso es muy bonito, pero a mí me sigue interesando el comportamiento real del algoritmo de ordenación sin más. Mis razones son:

   + No quiero la carga adicional de comprobar cada vez si los datos ya están ordenados. Si llamo a una función que ordena, probablemente lo hago porque los datos no están ordenados.
   + La comprobación no aporta ningún ahorro de tiempo cuando los datos están _casi_ ordenados.

De hecho, el caso de los datos _casi_ ordenados es muy importante. Diré que un algoritmo de ordenación tarda **O(N)** en el mejor caso si:

   + Tarda **O(N)** para datos ya ordenados (sin comprobaciones adicionales) **Y**
   + Tarda _casi_ **O(N)** para datos _casi_ ordenados.

Esta es una propiedad natural de la ordenación por inserción y, en cierta medida, también de la burbuja pero estos algoritmos tardan **O(N<sup>2</sup>)** de media.

El la liga de los **O(N log N)**, el mejor tiempo habitual es también **O(N log N)**. Así se comportan quick sort, heap sort, shell sort, comb sort y la implementación habitual de merge sort. Las notables excepciones son smooth sort y la variante _natural_ merge sort.

Precisamente, el nombre de smooth sort tiene su origen en esta propiedad. Cuando la entrada cambia de ordenada a _casi_ ordenada, y después a menos y aún menos ordenada, el tiempo de ejecución sufre una transición suave (_smooth_, en inglés) de **O(N)** a **O(N log N)**.

Heap sort es un caso especial. Si se implementa con cuidado y **sin** la optimización de Floyd, tarda **O(N)** cuando todos los datos de entrada son iguales. La transición de **O(N)** a **O(N log N)** es suave. Es decir, si _casi todos_ los datos son iguales, tarda _casi_ **O(N)**. No obstante, "datos iguales" es un caso especialmente restrictivo de "datos ya ordenados". En este sentido, heap sort no es comparable con smooth sort o con merge sort _natural_.


<br><br>
<a href='../LICENSE'><img src='../img/cc_by_88x31.png' alt='Creative Commons License' /></a><br>
**Autor:** [Martín Knoblauch Revuelta](http://www.mkrevuelta.com/es/acerca-de-mi/)<br>
El contenido de esta página está bajo una [licencia de Creative Commons Reconocimiento 3.0 Unported](../LICENSE)</a>

