# Explicación del término "ordenación estable"

Cuando se enseñan algoritmos de ordenación se suelen usar números. Lo más habitual es ordenar de menor a mayor. A veces también se introduce la pequeña sofisticación de ordenar de mayor a menor. En cualquier caso, si dos números son iguales, da lo mismo usar uno que otro.

En la vida real, sin embargo, las cosas son un poco más complicadas. Yo puedo ordenar mis libros conforme a muchos criterios diferentes:

   + Por orden alfabético del título
   + Por orden alfabético de autor...
      - ...según nombre-apellidos
      - ...según apellidos-nombre
   + Por año de edición
   + Por género (novela, cuento, fábula, ensayo, tratado, manual técnico, guía turística...)

Supongamos que mis libros están ya ordenados por orden alfabético de título, y los ordeno por año de edición, de menor a mayor. En un extremo quedarán los más antiguos y en otro extremo quedarán los más recientes. Los del año 2000, por ejemplo, estarán todos juntos.

Pero dentro del grupo de libros del año 2000, ¿cómo estarán ordenados entre sí? Si he utilizado un algoritmo de ordenación **estable**, los libros del año 2000 estarán juntos y ordenados entre sí por orden alfabético de título. Si he utilizado un algoritmo de ordenación **no estable**, los libros del año 2000 estarán juntos, pero revueltos (ordenados entre sí de cualquier manera).

La clave está en que los algoritmos de ordenación estables respetan el orden relativo de los elementos que se consideran _iguales_ según el criterio de ordenación que utilizan.

Los siguientes algoritmos realizan una ordenación estable:

   + Inserción (_insertion sort_)
   + Burbuja (_bubble sort_)
   + Mezcla (_merge sort_)

Los siguientes algoritmos realizan una ordenación *no* estable::

   + Selección (_selection sort_)
   + Rápido (_quick sort_)
   + Montículo (_heap sort_)
   + Shell (_Shell sort_)
   + Peine (_comb sort_)
   + Suave (_smooth sort_)

El único algoritmo de la categoría de tiempo **O(N log N)** (ver [notación de la "O grande"](BigOhNotation.md)) que realiza una ordenación estable es el de la mezcla (_merge sort_). El principal (y quizás el único) inconveniente de este algoritmo es que necesita **O(N)** espacio adicional. Curiosamente, cualquier algoritmo de ordenación no estable puede hacer una ordenación estable mediante el uso de **O(N)** espacio adicional.


<br><br>
<a href='../LICENSE'><img src='../img/cc_by_88x31.png' alt='Creative Commons License' /></a><br>
**Autor:** [Martín Knoblauch Revuelta](http://www.mkrevuelta.com/es/acerca-de-mi/)<br>
El contenido de esta página está bajo una [licencia de Creative Commons Reconocimiento 3.0 Unported](../LICENSE)</a>

