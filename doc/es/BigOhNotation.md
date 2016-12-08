# Complejidad computacional y notación de la "O grande"

<p align="right"><i>This page is in Spanish. If you prefer, you can read the <a href="../en/BigOhNotation.md">English version</a></i></p>

## Introducción

La [complejidad computacional](http://es.wikipedia.org/wiki/Teor%C3%ADa_de_la_complejidad_computacional) de un algoritmo es una medida del tiempo y el espacio (en memoria) que requiere su ejecución, en función del tamaño del problema.

La notación de la ["O grande"](http://es.wikipedia.org/wiki/Cota_superior_asint%C3%B3tica) se usa para describir la relación de esos dos parámetros (tiempo y espacio) con el tamaño del problema.

La documentación de este proyecto utiliza la notación de la "O grande" para describir y comparar los distintos algoritmos de ordenación. Esta página explica informalmente lo necesario para comprender el uso de dicha notación.

## Un ejemplo ilustrativo

Supongamos que tenemos tres ciudades **A**, **B** y **C**. Queremos ordenarlas de menor a mayor según su número de habitantes. Podríamos intentar ordenarlas aplicando el siguiente algoritmo:

  + Probar cada una de las 6 permutaciones posibles (**ABC**, **ACB**, **BAC**, **BCA**, **CAB** y **CBA**). Con cada una:
    - Recorrer la permutación elegida **xyz** comparando la población de cada ciudad con la siguiente. Si la población de **x** es menor que la de **y**, y la de **y** es menor que la de **z**, hemos terminado.

Puesto que sólo hay seis permutaciones posibles, este algoritmo ordenará las tres ciudades en muy poco tiempo. No se puede decir que tarda lo que un abrir y cerrar de ojos, porque un abrir y cerrar de ojos es una eternidad en comparación.

Sin embargo, ¿cómo se portará ese algoritmo si aumentamos el número de ciudades?

Si añadimos una cuarta ciudad **D**, el número de permutaciones se multiplica por cuatro, porque podemos insertar la **D** en cuatro posiciones distintas de cada una de las permutaciones de tres ciudades: **xyzD**, **xyDz**, **xDyz**, y **Dxyz**. En total tenemos veinticuatro permutaciones posibles: **ABCD**, **ABDC**, **ADBC**, **DABC**; **ACBD**, **ACDB**, **ADCB**, **DACB**; **BACD**... y así sucesivamente.

Si añadimos una quinta ciudad **E**, esas veinticuatro permutaciones se multiplican por cinco, dando un total de ciento veinte nada menos. Sigue siendo mucho menos tiempo que un abrir y cerrar de ojos, pero no es buena señal. Además, analizar cada permutación cuesta ahora cuatro comparaciones, mientras que con tres ciudades sólo costaba dos. En total se harán hasta 480 comparaciones, mientras que con tres ciudades sólo se hacían un máximo de 12. ¡Ordenar cinco ciudades requiere cuarenta veces más tiempo que ordenar tres!

En general, con **N** ciudades tendremos **N×(N-1)×(N-2)×...×1** permutaciones, es decir, **N!** (**N** "factorial"). Con 62 ciudades tenemos 62! = 31469973260387937525653122354950764088012280797258232192163168247821107200000000000000 permutaciones. Es un número tan grande que conviene expresarlo en notación científica: 62! ≈ 3'15×10<sup>85</sup>. ¡Esta cantidad es mayor que el número estimado de partículas elementales existentes en todo el universo observable!

Queda claro que este algoritmo es absurdamente lento. Tan lento que no es práctico ni para ordenar unas pocas decenas de elementos. Un buen programador debe estar entrenado para llegar a esta conclusión a primera vista, sin necesidad de programar y ejecutar el algoritmo.

## Tiempo

El algoritmo anterior realiza como máximo **N!×(N-1)** comparaciones para ordenar **N** ciudades. Además necesitará ejecutar otras operaciones elementales, pero el número total siempre será proporcional a **N!×(N-1)**. Si necesita alguna cantidad fija adicional de tiempo al principio o al final, la despreciaremos. También despreciaremos cualquier factor constante que multiplique el tiempo total. No nos interesa calcular el tiempo exacto para ningún **N** determinado. Nos interesa la evolución a largo plazo. Por eso nos limitaremos a decir que como máximo tarda un tiempo proporcional a **N!×(N-1)**.

Cabe destacar que el algoritmo anterior realizaría sólo **N-1** comparaciones en el mejor de los casos, es decir, cuando la primera permutación analizada resulte ser la del orden deseado.

Distinguiremos también el caso medio. En el algoritmo anterior, suponiendo que existe la misma probabilidad para todas las permutaciones, el caso medio requerirá la mitad de tiempo que el peor caso. Como se trata de un factor constante, lo despreciaremos. Consideraremos que el tiempo del peor caso y el tiempo del caso medio pertenecen a la misma categoría.

**Continuará...**


<br><br>
<a href='../LICENSE'><img src='../img/cc_by_88x31.png' alt='Creative Commons License' /></a><br>
**Autor:** [Martín Knoblauch Revuelta](http://www.mkrevuelta.com/es/acerca-de-mi/)<br>
El contenido de esta página está bajo una [licencia de Creative Commons Reconocimiento 3.0 Unported](../LICENSE)</a>

