# Analizador de estadísticas — Premier League 2025-2026

**Proyecto de Estructuras de Datos y Algoritmos — Avance 1**

Programa de consola en C++ que carga, organiza, ordena, filtra, busca y exporta las estadísticas de **300 jugadores reales de la Premier League 2025-2026** (15 por cada uno de los 20 equipos).

## 1. Descripción del proyecto

### ¿Qué hace?

El programa lee un archivo CSV con las estadísticas de cada jugador (goles, asistencias, minutos, partidos, tarjetas, etc.) y, desde un menú de consola, permite:

- **Cargar** los datos validando cada línea del archivo (campos faltantes, números inválidos, datos imposibles).
- **Mostrar** los jugadores en una tabla alineada, incluyendo un atributo derivado: **goles por cada 90 minutos**.
- **Ordenar** por 11 criterios distintos (numéricos y alfabéticos), en orden ascendente o descendente, eligiendo entre **Bubble Sort** y **Merge Sort** (ambos programados desde cero).
- **Obtener el Top N de goleadores** de la liga.
- **Filtrar** por equipo, posición, nacionalidad o por rangos de goles, asistencias, edad y minutos.
- **Buscar** un jugador por nombre con **búsqueda secuencial** o **búsqueda binaria**.
- **Exportar** el resultado actual (lo último que se ordenó o filtró) a un nuevo archivo CSV.

### ¿Por qué elegí este tema?

Me gusta el fútbol y sigo la Premier League, así que trabajar con sus datos hace que el proyecto sea más interesante para mí. Además, las estadísticas de jugadores son un buen caso para practicar los algoritmos y temas de la materia:

- Cada jugador tiene **atributos numéricos** (goles, minutos, edad…) y **de texto** (nombre, equipo, nacionalidad), así que un mismo algoritmo de ordenamiento se puede probar con criterios muy diferentes.
- Son preguntas que realmente se hacen los aficionados: ¿quién es el máximo goleador?, ¿qué jugadores de Arsenal tienen más asistencias?, ¿quiénes jugaron más minutos?
- Con ~300 registros ya se nota claramente la diferencia entre un algoritmo O(n²) y uno O(n log n).

### Sobre los datos

- Archivo: `data/jugadores.csv`, 300 jugadores, 15 por equipo, 20 equipos.
- Los nombres, equipos y nacionalidades corresponden a jugadores reales de la temporada 2025-2026. **Las estadísticas son aproximaciones realistas**, no cifras oficiales.
- Los nombres y nacionalidades se escriben **sin acentos ni caracteres especiales** (por ejemplo `Martin Odegaard`, `Espana`). Así la tabla se alinea bien en cualquier terminal y la búsqueda por nombre funciona igual en Windows, Mac y Linux. Por la misma razón, los mensajes de la consola tampoco llevan acentos.
- Cabecera del CSV:

```
nombre,equipo,posicion,edad,nacionalidad,partidos_jugados,partidos_titular,minutos,goles,asistencias,tarjetas_amarillas,tarjetas_rojas
```

## 2. Cómo usar el programa

### Compilación

Desde la carpeta principal del proyecto:

```bash
g++ src/*.cpp -o analizador
```

- `src/*.cpp` compila todos los archivos `.cpp` de la carpeta `src`.
- `-o analizador` le pone ese nombre al ejecutable (sin esto se llamaría `a.exe` o `a.out`).

El programa compila sin errores y **sin warnings** aun activando las advertencias del compilador (`-Wall`).

### Ejecución

También desde la carpeta principal (para que la ruta `data/jugadores.csv` funcione):

```bash
./analizador          # Linux / Mac
.\analizador.exe      # Windows (PowerShell)
```

### Menú

```
==== ANALIZADOR PREMIER LEAGUE ====
Jugadores cargados: 300  (data/jugadores.csv)
Resultado actual:   300 jugadores | todos los jugadores | orden: original del CSV
-----------------------------------
1. Cargar jugadores desde CSV
2. Mostrar todos los jugadores
3. Ordenar jugadores
4. Mostrar Top N goleadores
5. Filtrar jugadores
6. Buscar jugador por nombre
7. Exportar resultado actual a nuevo CSV
0. Salir
```

Arriba del menú siempre se ve cuántos jugadores hay cargados y qué contiene el **resultado actual**: la última lista que se mostró, filtró u ordenó. Esa es la lista que se ordena (opción 3), en la que se busca (opción 6) y la que se exporta (opción 7). Así se pueden combinar operaciones, por ejemplo: *filtrar Arsenal → ordenar por asistencias → exportar*.

| Opción | Qué hace |
|---|---|
| **1. Cargar** | Pide la ruta del CSV (con Enter usa `data/jugadores.csv`). Valida cada línea y reporta las que ignora y por qué. Si el archivo no existe o no tiene datos válidos, se conservan los datos que ya estaban cargados. |
| **2. Mostrar todos** | Muestra los 300 jugadores en orden del CSV y hace que el resultado actual vuelva a ser la lista completa. |
| **3. Ordenar** | Pide el criterio (1 = goles, 2 = asistencias, 3 = edad, 4 = minutos, 5 = partidos jugados, 6 = partidos titular, 7 = tarjetas amarillas, 8 = tarjetas rojas, 9 = nombre, 10 = equipo, 11 = nacionalidad), el orden (ascendente/descendente) y el algoritmo (a = Bubble Sort, b = Merge Sort). Imprime **el algoritmo usado y cuántos jugadores procesó**, y luego pregunta cuántos mostrar. |
| **4. Top N goleadores** | Ordena una copia de todos los jugadores por goles (descendente) con Merge Sort y muestra los primeros N. |
| **5. Filtrar** | Por equipo, posición o nacionalidad (se elige de una lista numerada, así no hay errores al escribir) o por rango de goles, asistencias, edad o minutos (mínimo y máximo, incluyendo ambos). |
| **6. Buscar** | Busca por nombre completo sin importar mayúsculas (`declan rice` = `Declan Rice`). (a) Secuencial funciona siempre. (b) Binaria requiere los datos ordenados por nombre A-Z: si no lo están, el programa lo avisa y ofrece ordenarlos con Merge Sort antes de buscar. |
| **7. Exportar** | Escribe el resultado actual en un nuevo CSV (con Enter usa `data/resultado.csv`) con la misma cabecera que el original, así que se puede volver a cargar con la opción 1. No permite sobrescribir el archivo original. |
| **0. Salir** | Termina el programa. |

**Validación de entradas:** todas las entradas se leen con `getline` y después se revisan. Si se escribe una letra donde va un número, un número fuera de rango, un máximo menor que el mínimo o una letra distinta de `a`/`b` o `s`/`n`, el programa muestra un mensaje y vuelve a preguntar, sin romperse ni quedarse en un ciclo infinito.

## 3. SICT0301 — Evalúa los componentes: análisis de complejidad

En todo el análisis, **n** es el número de jugadores que se procesan (300 si es la lista completa).

### Bubble Sort (`Ordenamientos.cpp`)

Recorre el vector comparando cada par de vecinos `v[j]` y `v[j+1]` y los intercambia si están en el orden incorrecto. Tras cada pasada, el elemento que debe ir al final queda en su lugar, por eso la pasada `i` compara un elemento menos.

| Caso | Complejidad temporal | ¿Cuándo pasa? |
|---|---|---|
| Mejor | **O(n)** | Los datos ya están ordenados |
| Promedio | **O(n²)** | Datos en orden aleatorio |
| Peor | **O(n²)** | Datos en orden inverso |

- **Peor y promedio, O(n²):** la primera pasada hace n−1 comparaciones, la segunda n−2, y así hasta 1. En total son (n−1) + (n−2) + … + 1 = **n(n−1)/2** comparaciones. En el peor caso (orden inverso) *cada* comparación termina en intercambio, así que también hay n(n−1)/2 intercambios. En el caso promedio se intercambia aproximadamente la mitad de las veces, pero n(n−1)/4 sigue siendo cuadrático. Con n = 300: 300·299/2 = **44,850 comparaciones**.
- **Mejor caso, O(n), gracias a la optimización:** la variable `huboIntercambio` registra si en una pasada se movió algo. Si los datos ya están ordenados, la primera pasada hace n−1 comparaciones, ningún intercambio, y el ciclo termina con `break`. Sin esta optimización el mejor caso también sería O(n²).
- **Espacial, O(1):** ordena *en el mismo vector* (in-place). Solo usa unas pocas variables (`pasada`, `j`, `huboIntercambio` y un `Jugador temporal` para el intercambio), sin importar cuántos jugadores haya.

### Merge Sort (`Ordenamientos.cpp`)

Usa la estrategia *divide y vencerás*: `mergeSortRecursivo` divide el rango a la mitad, se llama a sí mismo con cada mitad y después `merge` mezcla las dos mitades ya ordenadas.

| Caso | Complejidad temporal |
|---|---|
| Mejor | **O(n log n)** |
| Promedio | **O(n log n)** |
| Peor | **O(n log n)** |
| **Espacial** | **O(n)** |

- **¿Por qué O(n log n)?** Al dividir siempre a la mitad se forma un árbol de recursión:
  - nivel 0: 1 parte de tamaño n
  - nivel 1: 2 partes de tamaño n/2
  - nivel k: 2ᵏ partes de tamaño n/2ᵏ

  La división termina cuando las partes miden 1, es decir cuando n/2ᵏ = 1 → **k = log₂ n niveles**. En cada nivel, `merge` recorre en total los n elementos (cada elemento se copia y se coloca una vez por nivel), así que el costo es **n por nivel × log₂ n niveles = O(n log n)**. Como ecuación de recurrencia: T(n) = 2T(n/2) + n.
- **¿Por qué es igual en todos los casos?** Merge Sort divide a la mitad *sin importar cómo vengan los datos*, y `merge` siempre copia y acomoda todos los elementos del rango. El orden inicial solo cambia un poco cuántas comparaciones se hacen dentro de `merge`, no el número de niveles ni el trabajo por nivel.
- **Espacial, O(n):** `merge` copia cada mitad en los vectores auxiliares `izquierda` y `derecha`. En la mezcla final (la de nivel 0) esos vectores juntos guardan los n elementos. Se destruyen al terminar cada `merge`, así que nunca hay más de O(n) memoria extra al mismo tiempo. Además, la recursión ocupa O(log n) en la pila de llamadas, que es menor que O(n).
- **Con n = 300:** log₂ 300 ≈ 8.2, así que hay 9 niveles y como máximo unas 300 × 9 = 2,700 operaciones de colocación.

### Búsqueda Secuencial (`Busquedas.cpp`)

Revisa los jugadores uno por uno desde el índice 0 hasta encontrar el nombre.

| Caso | Complejidad temporal | ¿Cuándo pasa? |
|---|---|---|
| Mejor | **O(1)** | El jugador está en la primera posición |
| Promedio | **O(n)** | En promedio revisa n/2 elementos |
| Peor | **O(n)** | Está al final o no existe (revisa los n) |
| Espacial | **O(1)** | Solo usa un índice y el texto buscado |

### Búsqueda Binaria (`Busquedas.cpp`)

Compara con el elemento de en medio y, como los datos están ordenados, descarta la mitad donde el nombre no puede estar.

| Caso | Complejidad temporal | ¿Cuándo pasa? |
|---|---|---|
| Mejor | **O(1)** | El jugador está justo en medio |
| Peor | **O(log n)** | Está en un extremo o no existe |
| Espacial | **O(1)** | Versión iterativa: solo `inicio`, `fin` y `mitad` |

- **¿Por qué O(log n)?** Después de cada comparación quedan n → n/2 → n/4 → … → 1 elementos. Después de k pasos quedan n/2ᵏ, y se llega a 1 cuando k = log₂ n. Con n = 300 son **como máximo 9 comparaciones**, contra 300 de la secuencial.
- **Requisito:** los datos deben estar **ordenados por nombre de forma ascendente**. Si no lo están, al descartar una mitad podría descartar justo la mitad donde está el jugador y responder "no encontrado" aunque sí exista. Por eso el programa guarda si el resultado actual está ordenado por nombre (`ordenadoPorNombre`) y, si no, ofrece ordenarlo primero con Merge Sort.
- El ordenamiento por nombre (criterio 9) y la búsqueda binaria comparan los nombres **en minúsculas**. Es importante que los dos usen exactamente la misma forma de comparar; si no, la búsqueda podría irse por la mitad equivocada.

### Comprobación con los datos reales

Para confirmar el análisis, agregué temporalmente un contador de comparaciones dentro de `vaDespues` (la función que usan ambos ordenamientos para comparar) y ordené los 300 jugadores:

| Prueba (n = 300) | Bubble Sort | Merge Sort |
|---|---:|---:|
| Goles, descendente (orden original del CSV) | 44,444 | 1,962 |
| Nombre, ascendente (orden original del CSV) | 44,679 | 2,103 |
| Asistencias, descendente (orden original del CSV) | 43,904 | 1,995 |
| Nombre, ascendente, **datos ya ordenados** (mejor caso) | **299** | 1,308 |
| Nombre, descendente, **datos en orden inverso** (peor caso) | **44,850** | 1,180 |
| Solo Arsenal (n = 15), goles descendente | 105 | 40 |

Los números coinciden con la teoría: el peor caso de Bubble Sort es exactamente n(n−1)/2 = 44,850, su mejor caso es n−1 = 299 (una sola pasada), y Merge Sort siempre queda por debajo de n·⌈log₂ n⌉ = 2,700. En la búsqueda binaria, el máximo fue de **9 iteraciones** para encontrar a cualquiera de los 300 jugadores.

> Nota: cuando el criterio es de texto, cada comparación convierte los dos textos a minúsculas, lo cual depende del largo del nombre (unos 25 caracteres como máximo). Es un costo constante por comparación, así que no cambia la complejidad de ningún algoritmo.

### Complejidad de las demás operaciones

| Operación | Complejidad temporal | Motivo |
|---|---|---|
| `cargarDesdeCSV` | O(n) | Lee y valida cada línea una vez |
| `mostrarTodos` / `mostrarLista` | O(n) | Imprime cada jugador una vez |
| Filtros (`filtrarPor...`) | O(n) | Recorren todos los jugadores una vez |
| `exportarACSV` | O(n) | Escribe cada jugador una vez |
| Top N goleadores | O(n log n) | Merge Sort de los n jugadores, más copiar N |
| `golesPor90Min` | O(1) | Una división |

## 4. SICT0302 — Toma decisiones: justificación

### ¿Por qué Merge Sort es el algoritmo principal?

1. **Eficiencia con el volumen de datos:** con 300 jugadores, Bubble Sort hace ~44,000 comparaciones y Merge Sort ~2,000, **más de 20 veces menos**. Como O(n²) crece mucho más rápido que O(n log n), la diferencia aumentaría con más datos: con 3,000 jugadores (por ejemplo, varias temporadas) Bubble Sort haría ~4.5 millones de comparaciones y Merge Sort unas 35,000.
2. **Rendimiento garantizado:** Merge Sort es O(n log n) en *todos* los casos. No importa si el usuario ordena datos que vienen por equipo, por goles o al revés, el tiempo es predecible.
3. **Es estable:** en un empate toma primero el elemento de la mitad izquierda, así que los jugadores empatados conservan su orden anterior. Esto sirve para combinar ordenamientos: si se ordena por nombre y después por goles, los jugadores con los mismos goles quedan en orden alfabético.
4. **Su desventaja no importa aquí:** Merge Sort usa O(n) memoria extra, pero con 300 jugadores eso es muy poco para cualquier computadora. Cambiar un poco de memoria por mucha velocidad es una buena decisión.

Por esto el programa usa Merge Sort internamente cuando no se le pregunta al usuario: en el **Top N goleadores** y al preparar los datos para la **búsqueda binaria**.

### ¿Cuándo conviene cada uno?

| Situación | Algoritmo recomendado | Razón |
|---|---|---|
| Muchos datos (cientos o miles) | **Merge Sort** | O(n log n) garantizado |
| Datos en orden aleatorio o inverso | **Merge Sort** | Bubble Sort llega a su peor caso O(n²) |
| Se necesita estabilidad | Cualquiera de los dos | Ambos son estables en esta implementación |
| Muy pocos datos (por ejemplo los 15 jugadores de un equipo filtrado) | **Bubble Sort** es suficiente | 105 comparaciones es muy poco y el código es más simple |
| Datos **casi ordenados** | **Bubble Sort** | Con la optimización termina en pocas pasadas (O(n) si ya están ordenados) |
| Memoria muy limitada | **Bubble Sort** | O(1) memoria extra contra O(n) de Merge Sort |

Por eso el menú deja elegir el algoritmo: sirve para comparar ambos en la demostración y para usar Bubble Sort cuando la lista es pequeña o ya casi está ordenada.

### ¿Por qué implementé búsqueda binaria además de la secuencial?

- **La secuencial no tiene requisitos:** funciona sobre cualquier lista, sin importar cómo esté ordenada (por ejemplo, después de un filtro o de ordenar por goles). Por eso es la opción segura.
- **La binaria es mucho más rápida:** como máximo 9 comparaciones contra 300. Ordenar por nombre cuesta O(n log n) *una sola vez*; después, cada búsqueda cuesta solo O(log n). Si el usuario va a buscar varios jugadores, ordenar primero y usar búsqueda binaria es más eficiente que hacer muchas búsquedas secuenciales de O(n).
- **Se evita un resultado incorrecto:** una búsqueda binaria sobre datos desordenados puede decir "no encontrado" aunque el jugador sí esté. El programa revisa esta condición y, en lugar de dar una respuesta equivocada, ofrece ordenar primero.

### Otras decisiones de diseño

- **Un criterio numérico (`int criterio`) con `switch`** en lugar de escribir un algoritmo distinto por cada atributo: un solo Bubble Sort y un solo Merge Sort sirven para los 11 criterios, y el parámetro `bool ascendente` invierte el orden.
- **Carga en un vector temporal:** si el archivo tiene errores o no existe, no se pierden los datos que ya estaban cargados.
- **Filtros que regresan un vector nuevo:** el registro original nunca se modifica, así que siempre se puede volver a la lista completa con la opción 2.
- **Lectura con `getline` y validación manual** (`convertirAEntero`) en lugar de `cin >> numero`, para que una letra donde va un número no rompa el programa.
- **Referencias constantes (`const vector<Jugador>&`, `const string&`)** en los parámetros para no copiar 300 jugadores cada vez que se llama a una función.

## 5. Estructura de archivos

```
futbol-data/
├── src/
│   ├── Jugador.h / Jugador.cpp            Clase Jugador: atributos privados, getters,
│   │                                      mostrar() y golesPor90Min() (atributo derivado)
│   ├── Registro.h / Registro.cpp          Clase Registro: vector<Jugador>, carga y validación
│   │                                      del CSV, mostrar, 7 filtros y exportar a CSV
│   ├── Ordenamientos.h / Ordenamientos.cpp  bubbleSort, mergeSort (+ mergeSortRecursivo y merge)
│   │                                      y la comparación por los 11 criterios
│   ├── Busquedas.h / Busquedas.cpp        busquedaSecuencial y busquedaBinaria por nombre
│   ├── Utilidades.h / Utilidades.cpp      Funciones de texto que usan varios módulos:
│   │                                      aMinusculas, limpiarEspacios, convertirAEntero
│   └── main.cpp                           Menú, lectura segura de entradas y las 7 opciones
├── data/
│   └── jugadores.csv                      300 jugadores (15 por equipo, 20 equipos)
├── README.md                              Este documento
├── LICENSE
└── .gitignore
```

`Utilidades` se separó en su propio archivo porque `Registro`, `Ordenamientos`, `Busquedas` y `main` necesitan las mismas funciones de texto; así no se repite el código en cada módulo.

## 6. Ejemplo de ejecución

Sesión real del programa (lo que escribe el usuario aparece después de cada `:`). Para no repetir, se omite el menú completo entre opciones.

```
==== ANALIZADOR PREMIER LEAGUE ====
(Aun no hay jugadores cargados)
-----------------------------------
1. Cargar jugadores desde CSV
2. Mostrar todos los jugadores
3. Ordenar jugadores
4. Mostrar Top N goleadores
5. Filtrar jugadores
6. Buscar jugador por nombre
7. Exportar resultado actual a nuevo CSV
0. Salir
Elige una opcion (0-7): hola
  Entrada invalida. Escribe un numero entero entre 0 y 7.
Elige una opcion (0-7): 1

--- CARGAR JUGADORES ---
Ruta del archivo (Enter = data/jugadores.csv):
>> Se cargaron 300 jugadores desde "data/jugadores.csv".

==== ANALIZADOR PREMIER LEAGUE ====
Jugadores cargados: 300  (data/jugadores.csv)
Resultado actual:   300 jugadores | todos los jugadores | orden: original del CSV
[...menu...]
Elige una opcion (0-7): 4

--- TOP N GOLEADORES ---
Cuantos goleadores quieres ver? (1-300): 5
>> Algoritmo usado: Merge Sort | Jugadores procesados: 300 | Criterio: goles (descendente)

#    Nombre                  Equipo            Posicion      Edad  Nacionalidad        PJ  PT   Min   G   A  TA  TR   G/90
--------------------------------------------------------------------------------------------------------------------------
1    Erling Haaland          Manchester City   Delantero       25  Noruega             36  35  2738  27   4   2   0   0.89
2    Igor Thiago             Brentford         Delantero       24  Brasil              36  35  2777  19   3   4   0   0.62
3    Viktor Gyokeres         Arsenal           Delantero       27  Suecia              35  31  2520  14   3   3   0   0.50
4    Jean-Philippe Mateta    Crystal Palace    Delantero       28  Francia             36  33  2627  13   2   3   0   0.45
5    Hugo Ekitike            Liverpool         Delantero       23  Francia             35  28  2309  13   4   3   0   0.51
--------------------------------------------------------------------------------------------------------------------------
Mostrando 5 de 5 jugadores.
PJ=partidos jugados  PT=partidos titular  Min=minutos  G=goles  A=asistencias  TA/TR=tarjetas amarillas/rojas  G/90=goles por 90 min

==== ANALIZADOR PREMIER LEAGUE ====
Jugadores cargados: 300  (data/jugadores.csv)
Resultado actual:   5 jugadores | Top 5 goleadores | orden: goles (descendente)
[...menu...]
Elige una opcion (0-7): 5

--- FILTRAR JUGADORES ---
(Los filtros se aplican sobre todos los jugadores cargados)
   1. Por equipo
   2. Por posicion
   3. Por nacionalidad
   4. Por rango de goles
   5. Por rango de asistencias
   6. Por rango de edad
   7. Por rango de minutos
   0. Volver al menu principal
Elige el tipo de filtro (0-7): 1
Equipos:
   1. Arsenal                  2. Aston Villa              3. Bournemouth
   4. Brentford                5. Brighton                 6. Burnley
   7. Chelsea                  8. Crystal Palace           9. Everton
  10. Fulham                  11. Leeds United            12. Liverpool
  13. Manchester City         14. Manchester United       15. Newcastle
  16. Nottingham Forest       17. Sunderland              18. Tottenham
  19. West Ham                20. Wolves
Elige una opcion (1-20): 1

#    Nombre                  Equipo            Posicion      Edad  Nacionalidad        PJ  PT   Min   G   A  TA  TR   G/90
--------------------------------------------------------------------------------------------------------------------------
1    David Raya              Arsenal           Portero         30  Espana              38  38  3420   0   0   2   0   0.00
2    William Saliba          Arsenal           Defensa         24  Francia             33  33  2874   2   1   3   0   0.06
[... 13 jugadores mas ...]
--------------------------------------------------------------------------------------------------------------------------
Mostrando 15 de 15 jugadores.
>> 15 jugadores cumplen el filtro (filtro: equipo = Arsenal).

==== ANALIZADOR PREMIER LEAGUE ====
Jugadores cargados: 300  (data/jugadores.csv)
Resultado actual:   15 jugadores | filtro: equipo = Arsenal | orden: original del CSV
[...menu...]
Elige una opcion (0-7): 3

--- ORDENAR JUGADORES ---
Se ordenara el resultado actual (15 jugadores: filtro: equipo = Arsenal).
Criterios:
   1 = goles               7 = tarjetas amarillas
   2 = asistencias         8 = tarjetas rojas
   3 = edad                9 = nombre (alfabetico)
   4 = minutos            10 = equipo (alfabetico)
   5 = partidos jugados   11 = nacionalidad (alfabetico)
   6 = partidos titular
Elige el criterio (1-11): 1
Orden:
   1 = Ascendente  (menor a mayor / A-Z)
   2 = Descendente (mayor a menor / Z-A)
Elige el orden (1-2): 2
Algoritmo:
   a) Bubble Sort
   b) Merge Sort
Elige el algoritmo (a/b): a

>> Algoritmo usado: Bubble Sort | Jugadores procesados: 15 | Criterio: goles (descendente)
Cuantos jugadores quieres ver? (0 = todos): 5

#    Nombre                  Equipo            Posicion      Edad  Nacionalidad        PJ  PT   Min   G   A  TA  TR   G/90
--------------------------------------------------------------------------------------------------------------------------
1    Viktor Gyokeres         Arsenal           Delantero       27  Suecia              35  31  2520  14   3   3   0   0.50
2    Bukayo Saka             Arsenal           Delantero       24  Inglaterra          33  30  2429   9   8   2   0   0.33
3    Eberechi Eze            Arsenal           Mediocampista   27  Inglaterra          35  25  2282   7   5   2   0   0.28
4    Leandro Trossard        Arsenal           Delantero       31  Belgica             34  22  1992   7   5   3   0   0.32
5    Gabriel Martinelli      Arsenal           Delantero       24  Brasil              31  13  1436   6   3   2   0   0.38
--------------------------------------------------------------------------------------------------------------------------
Mostrando 5 de 15 jugadores.
PJ=partidos jugados  PT=partidos titular  Min=minutos  G=goles  A=asistencias  TA/TR=tarjetas amarillas/rojas  G/90=goles por 90 min
>> Ordenado con Bubble Sort: 15 jugadores procesados por goles (descendente).

==== ANALIZADOR PREMIER LEAGUE ====
Jugadores cargados: 300  (data/jugadores.csv)
Resultado actual:   15 jugadores | filtro: equipo = Arsenal | orden: goles (descendente)
[...menu...]
Elige una opcion (0-7): 6

--- BUSCAR JUGADOR POR NOMBRE ---
Se buscara en el resultado actual (15 jugadores: filtro: equipo = Arsenal).
Escribe el nombre completo sin acentos (ej. Mohamed Salah, Martin Odegaard).
Nombre: declan rice
Metodo de busqueda:
   a) Busqueda secuencial
   b) Busqueda binaria (requiere datos ordenados por nombre A-Z)
Elige el metodo (a/b): b
  Aviso: la busqueda binaria requiere que los datos esten ordenados por nombre (A-Z).
  El resultado actual esta ordenado por: goles (descendente).
  Ordenarlo ahora por nombre con Merge Sort? (s/n): s
>> Algoritmo usado: Merge Sort | Jugadores procesados: 15 | Criterio: nombre (ascendente)
>> Busqueda binaria: jugador encontrado en el indice 2 del resultado actual.

#    Nombre                  Equipo            Posicion      Edad  Nacionalidad        PJ  PT   Min   G   A  TA  TR   G/90
--------------------------------------------------------------------------------------------------------------------------
1    Declan Rice             Arsenal           Mediocampista   27  Inglaterra          37  37  3024   5   7   5   0   0.15
--------------------------------------------------------------------------------------------------------------------------
Mostrando 1 de 1 jugadores.

==== ANALIZADOR PREMIER LEAGUE ====
Jugadores cargados: 300  (data/jugadores.csv)
Resultado actual:   15 jugadores | filtro: equipo = Arsenal | orden: nombre (ascendente)
[...menu...]
Elige una opcion (0-7): 7

--- EXPORTAR RESULTADO ACTUAL ---
Se exportaran 15 jugadores (filtro: equipo = Arsenal, orden: nombre (ascendente)).
Ruta del nuevo archivo (Enter = data/resultado.csv):
>> Se exportaron 15 jugadores a "data/resultado.csv".

[...menu...]
Elige una opcion (0-7): 0
Gracias por usar el analizador. Hasta luego!
```

Fíjate en el ordenamiento con Bubble Sort: **Eze y Trossard empatan con 7 goles** y conservan el orden que tenían antes (Eze aparece primero en el CSV). Eso muestra que el algoritmo es **estable**.

### Ejemplo de validación al cargar un CSV con errores

Para probarlo, crea un archivo `data/prueba_errores.csv` con este contenido (la línea 3 está vacía a propósito, las líneas vacías se saltan sin error):

```
nombre,equipo,posicion,edad,nacionalidad,partidos_jugados,partidos_titular,minutos,goles,asistencias,tarjetas_amarillas,tarjetas_rojas
Bukayo Saka,Arsenal,Delantero,24,Inglaterra,33,30,2500,9,8,2,0

Sin Campos,Arsenal,Delantero,24
Letra Mal,Arsenal,Delantero,24,Inglaterra,33,30,2500,diez,8,2,0
Pos Mal,Arsenal,Arquero,24,Inglaterra,33,30,2500,9,8,2,0
Titular Mal,Arsenal,Delantero,24,Inglaterra,10,30,2500,9,8,2,0
Edad Mal,Arsenal,Delantero,7,Inglaterra,10,3,250,9,8,2,0
,Arsenal,Delantero,24,Inglaterra,33,30,2500,9,8,2,0
Negativo,Arsenal,Delantero,24,Inglaterra,33,30,2500,-3,8,2,0
  Con Espacios  , Chelsea ,Defensa, 25 ,Espana,1,1,90,0,0,0,0
```

Al cargarlo con la opción 1:

```
Ruta del archivo (Enter = data/jugadores.csv): data/prueba_errores.csv
  Linea 4 ignorada: se esperaban 12 campos y tiene 4.
  Linea 5 ignorada: el campo 'goles' no es un numero valido ("diez").
  Linea 6 ignorada: posicion desconocida ("Arquero").
  Linea 7 ignorada: tiene mas partidos de titular que partidos jugados.
  Linea 8 ignorada: edad fuera de rango (7).
  Linea 9 ignorada: tiene campos de texto vacios.
  Linea 10 ignorada: el campo 'goles' no es un numero valido ("-3").
  Aviso: se ignoraron 7 lineas con errores.
>> Se cargaron 2 jugadores desde "data/prueba_errores.csv".
```

Si el archivo no existe:

```
Ruta del archivo (Enter = data/jugadores.csv): no/existe.csv
  Error: no se pudo abrir el archivo "no/existe.csv".
  Revisa que la ruta sea correcta y que ejecutes el programa desde la carpeta principal del proyecto.
```
