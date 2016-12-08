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

### Tiempo constante: O(1)

Diremos que un algoritmo tarda un tiempo **O(1)** cuando su tiempo de ejecución no dependa de **N** (el tamaño del problema). Por ejemplo:

```C
double elemento_central (const double A[],        // Array de números
                         unsigned num)            // Tamaño del array
{
    return A[num/2];                    // Devolver el valor que haya
}                                       // en la posición central
```

La función `elemento_central()` siempre tardará el mismo tiempo en ejecutarse, sea cual sea el tamaño del array.

La siguiente función también tarda un tiempo **O(1)**:

```C
double suma_aleatoria (const double A[],          // Array de números
                       unsigned num)              // Tamaño del array
{
    unsigned i;
    double suma;                     // Sumar 327 elementos del array
                                     // escogidos al azar (podría
    for (i=0, suma=0; i<327; i++)    // sumarse varias veces un mismo
        suma += A[rand()%num];       // elemento)
        
    return suma;
}
```

Tardará mucho más tiempo que la anterior, pero debemos considerarla **O(1)** porque es una cantidad de tiempo constante. No depende de si el array tiene tres elementos o tres millones.

En caso de compararlas entre sí, diremos que ambas tardan **O(1)**, pero que el factor constante es mucho más elevado en `suma_aleatoria()` que en `elemento_central()`.

### Tiempo logarítmico: O(log N)

La siguiente función suma los elementos de ciertas posiciones de un array:

```C
double suma_potencias_3 (const double A[],        // Array de números
                         unsigned num)            // Tamaño del array
{
    unsigned i;
    double suma;
                                     // Sumar los elementos del array
    for (i=1, suma=0; i<num; i*=3)   // cuyo índice sea una potencia
        suma += A[i];                // de 3 (incluída la posición 1)
        
    return suma;
}
```

Observe que la condición para permanecer en el bucle es `i<num`, pero la variable `i` no se incrementa en una unidad en cada iteración, sino que se multiplica por 3. La condición del bucle dejará de cumplirse cuando **3<sup>x</sup> ≥ N**, donde **x** es el número de iteraciones y **N** es el valor de `num`. Despejando, obtenemos que **x ≈ log<sub>3</sub>N**.

La base del logaritmo es irrelevante porque los logaritmos de un mismo número en dos bases diferentes guardan entre sí una proporción fija. Es decir, **log<sub>a</sub>N = k×log<sub>b</sub>N**, donde **k** es constante (concretamente, **k = log<sub>a</sub>b**).

La siguiente función también tarda **O(log N)**:

```C
unsigned contar_unos (unsigned n)     // Contar número de unos de la
{                                     // representación binaria de n
    unsigned unos;
    
    for (unos=0; n; n>>=1)        // Mientras n!=0, sumar a 'unos'
        unos += n & 1;            // el bit bajo de 'n', y desplazar
                                  // 'n' un bit a la derecha
    return unos;
}
```

En los ordenadores de hoy en día, el tipo `unsigned` suele ser de 32 bits. Eso impone un límite relativamente bajo al número de iteraciones que ejecutarán los bucles de las dos funciones anteriores. Por eso es habitual que en algunos contextos se las considere **O(1)**. Técnicamente no lo son, pero ambas son más rápidas que la función `suma_aleatoria()` del apartado anterior.

La conclusión es que a la hora de comparar algoritmos **O(1)** con algoritmos **O(log N)** hay que tener en cuenta los factores constantes.

### Tiempo lineal: O(N)

La siguiente función tarda **O(N)**:

```C
double media (const double A[],                   // Array de números
              unsigned num)                       // Tamaño del array
{
    unsigned i;
    double suma;
                                        // Sumar todos los elementos
    for (i=0, suma=0; i<num; i++)       // del array para calcular la
        suma += A[i];                   // media aritmética
        
    return num ? suma/num : 0;          // Si num==0, evitar división
}                                       // (entre cero) y devolver 0
```

En el siguiente caso no es tan obvio, pero también tarda un tiempo **O(N)**. Lo que la función hace con los datos del array es irrelevante. Observe cuidadosamente la relación entre los dos bucles:

```C
void faa (double A[],                             // Array de números
          unsigned num)                           // Tamaño del array
{
    unsigned i, j;
    
    for (i=0; i<num; i++)
        for (j=i; j<num && A[j]!=3; j++)
            A[--num] *= 2;                 // OJO: Cambiar num afecta
}                                          //      al bucle externo
```

### Tiempo lineal-logarítmico: O(N log N)

La siguiente función contiene dos bucles anidados:

```C
unsigned fee (const double A[],                   // Array de números
              unsigned num)                       // Tamaño del array
{
    unsigned i, c, m;
    
    for (c=0, m=num; m; m>>=1)           //   log(N) iteraciones *
        for (i=0; i<num; i++)            //        N iteraciones   =
            if (i!=m-1 && A[i]==A[m-1])  // N*log(N) iteraciones
                c ++;

    return c;
}
```

El bucle externo ejecutará log<sub>2</sub>(`num`) iteraciones. En cada una de ellas, el bucle interno ejecutará `num` iteraciones. Por lo tanto, el número total de veces que se ejecuta la sentencia `if` será `num`×log<sub>2</sub>(`num`).

### Tiempo cuadrático: O(N<sup>2</sup>)

La siguiente función contiene dos bucles anidados. Ambos realizan `num` iteraciones cada vez, por lo que el número total de iteraciones del bucle interno será `num`<sup>2</sup>.

```C
unsigned fii (const double A[],                   // Array de números
              unsigned num)                       // Tamaño del array
{
    unsigned i, j, c;
    
    for (i=c=0; i<num; i++)              //   N iteraciones *
        for (j=0; j<num; j++)            //   N iteraciones   =
            if (i<j && A[i]>A[j])        // N*N iteraciones
                c ++;

    return c;
}
```

La siguiente función es una versión optimizada de la anterior. Observe que se ha eliminado la comparación `i<j` y se ha cambiado el valor inicial de `j` en el bucle interno. Obtendrá el mismo resultado que `fii()`, pero en la mitad de tiempo. No obstante, sigue siendo **O(N<sup>2</sup>)** porque lo único que ha cambiado es el factor constante:

```C
unsigned foo (const double A[],                   // Array de números
              unsigned num)                       // Tamaño del array
{
    unsigned i, j, c;
    
    for (i=c=0; i<num; i++)
        for (j=i+1; j<num; j++)          // (N-1)+(N-2)+...+(1) =
            if (A[i]>A[j])               // N*N/2 iteraciones (aprox)
                c ++;

    return c;
}
```

### Tiempo polinómico: O(N<sup>3</sup>), O(N<sup>4</sup>)...

**O(N<sup>3</sup>)**:

```C
    for (i=0; i<num; i++)
        for (j=0; j<num; j++)
            for (k=0; k<num; k++)
                // ... hacer algo O(1) aquí ...
```

**O(N<sup>4</sup>)**:

```C
    for (i=0; i<num; i++)
        for (j=0; j<num; j++)
            for (k=0; k<num; k++)
                for (m=0; m<num; m++)
                    // ... hacer algo O(1) aquí ...
```

... y así sucesivamente.

Ojo: en sentido estricto, **O(1)**, **O(N)** y **O(N<sup>2</sup>)** también son _polinómicos_, porque **1**, **N** y **N<sup>2</sup>** son polinomios (de grados 0, 1 y 2 respectivamente).

### Otras complejidades: O(N!)...

Está claro que hay que evitar, en la medida de lo posible, algoritmos absurdamente lentos como el descrito al principio de esta página. No obstante, existen algunos problemas para los que no se conoce ningún algoritmo que termine en tiempo polinómico, como el [problema del viajante](http://es.wikipedia.org/wiki/Problema_del_viajante) o el [problema de la mochila](http://es.wikipedia.org/wiki/Problema_de_la_mochila).

## Espacio

La notación de la "O grande" también se emplea para describir la cantidad de memoria adicional que necesita un algoritmo en función del tamaño del problema. Se especifica _adicional_ porque no se incluye el espacio ocupado por los datos de entrada o salida del problema.

Si una función sólo declara algunas variables de tipos primitivos (`int`, `float`, etc.) o arrays de tamaño fijo, se considera que sólo requiere **O(1)** espacio adicional. Si utiliza un array de tamaño **N**, se considera que necesita **O(N)** espacio adicional, y así sucesivamente.

## Atención a la recursividad

La siguiente función calcula el factorial de un número en tiempo **O(N)** y con **O(1)** espacio adicional:

```C
double factorial_iter (unsigned n)
{
    double f;
    
    for (f=1; n>1; n--)
        f *= n;
        
    return f;
}
```

La siguiente función calcula lo mismo pero utilizando recursividad:

```C
double factorial_rec (unsigned n)
{
    return n<=1 ? 1                       // Si n<=1, fin
                : n * factorial_rec(n-1); // Si no, llamada recursiva
}
```

La versión recursiva también tarda **O(N)**, pero es considerablemente más lenta. El factor constante es mayor porque una llamada a una función tarda mucho más que una iteración de un bucle.

Pero además, como se hacen `n-1` llamadas recursivas anidadas, se emplea **O(N)** espacio adicional. Cada llamada usa algo de memoria para _recordar_ por dónde seguir a la vuelta, para almacenar el parámetro `n` (hay un `n` distinto por cada llamada) y para depositar el valor devuelto por la función.

Veamos otro ejemplo de lo que no se debe hacer:

```C
unsigned fibonacci (unsigned n)       // Números de Fibonacci:
{                                     // 0, 1, 1, 2, 3, 5, 8, 13, ...
    return n==0 ? 0 :
           n==1 ? 1 :                 // Salvo los dos primeros,
                  fibonacci(n-1) +    // cada número es la suma de
                  fibonacci(n-2);     // los dos anteriores
}
```

En este caso el tiempo de ejecución se dispara hacia **O(2<sup>N</sup>)**. El número de llamadas no es exactamente **2<sup>N</sup>**, pero está entre **2<sup>N</sup>** y **2<sup>N/2</sup>**. A efectos prácticos da lo mismo: es una función absurdamente lenta. Es especialmente absurda porque calcula los mismos números muchas veces.

El espacio adicional requerido es _sólo_ **O(N)** porque la secuencia de llamadas recursivas anidadas más larga es proporcional a **N**.

La siguiente función calcula lo mismo en tiempo **O(N)** con sólo **O(1)** espacio adicional:

```C
unsigned fibonacci_iter (unsigned n)  // Números de Fibonacci:
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

## Más información

Para más información sobre el significado exacto de **O**, **Θ**, **Ω** y **ω**, véase:

  + **O**: [Cota superior asintótica](http://es.wikipedia.org/wiki/Cota_superior_asint%C3%B3tica)
  + **Ω**: [Cota inferior asintótica](http://es.wikipedia.org/wiki/Cota_inferior_asint%C3%B3tica)
  + **Θ**: [Cota ajustada asintótica](http://es.wikipedia.org/wiki/Cota_ajustada_asint%C3%B3tica)


<br><br>
<a href='../LICENSE'><img src='../img/cc_by_88x31.png' alt='Creative Commons License' /></a><br>
**Autor:** [Martín Knoblauch Revuelta](http://www.mkrevuelta.com/es/acerca-de-mi/)<br>
El contenido de esta página está bajo una [licencia de Creative Commons Reconocimiento 3.0 Unported](../LICENSE)</a>

