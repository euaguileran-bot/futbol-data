# Analizador de estadísticas — Premier League 2025-2026

**Estructuras de Datos y Algoritmos — Proyecto final (Avance 3)**

## 1. Descripción del proyecto

Programa en C++ que carga desde un CSV las estadísticas de **300 jugadores reales de la Premier League 2025-2026** (15 por equipo). Las guarda en estructuras de datos programadas a mano:

- **Lista doblemente ligada:** almacenamiento principal, en el orden de carga. Ahí se agregan, actualizan y eliminan jugadores.
- **Árbol binario de búsqueda (BST)** ordenado por nombre: para buscar rápido y obtener el orden alfabético.
- **Heap máximo:** para sacar el Top N por un criterio.

Con ellas, el programa permite cargar, mostrar, ordenar (con Bubble Sort o Merge Sort), filtrar, buscar, agregar, actualizar y eliminar jugadores, y **guardar los cambios** en el mismo CSV.

Elegí este tema porque me gusta el fútbol y sigo la Premier League. Además, cada jugador tiene muchos atributos, así que un mismo algoritmo se puede probar con distintos criterios. Las estadísticas del archivo son aproximadas.

### Cambios respecto al Avance 2

- **Retroalimentación:** el profesor no pidió cambios. Comentó que el programa es claro y explícito en el uso de las estructuras, así que **mantuve el mismo estilo**: cada opción dice en pantalla qué estructura o archivo usa. Por ejemplo: "Buscando en el arbol BST...", "Sacando el Top 5 del heap...", "Escribiendo la lista doble en data/jugadores.csv...".
- **Guardar (nuevo):** escribe la lista doble en `data/jugadores.csv`. Antes hace un respaldo en `data/jugadores_respaldo.csv`, y si hay cambios sin guardar avisa al salir o al recargar.
- **Agregar, actualizar y eliminar:** se necesitan para que guardar tenga sentido. Siempre dejan la lista y el árbol sincronizados.
- **Heap (`Heap.h`, nuevo):** se usa para el Top N.

## 2. Valor para el usuario final (SEG0701)

**¿Quién lo usaría?** Un aficionado, un jugador de *fantasy football* o alguien que analiza o escribe sobre la liga. Tiene a los 300 jugadores en un solo lugar y puede consultarlos, compararlos y mantenerlos al día sin una hoja de cálculo.

**Ejemplos de uso:**

1. **Fantasy:** antes de armar su equipo, pide el **Top 10 por asistencias** (opción 7) y ve quién genera más jugadas de gol.
2. **Seguir la temporada:** después de una jornada, **actualiza** los goles y minutos de sus jugadores (opción 9) y **guarda** (opción 11). La próxima vez que abra el programa, los datos siguen ahí.
3. **Mercado de fichajes:** **elimina** a un jugador que se fue de la liga (opción 10), **agrega** a uno que llegó (opción 8) validando su equipo y posición, y revisa la plantilla de su club con el **filtro por equipo** (opción 4).

## 3. Cómo usar el programa

```bash
g++ src/*.cpp -o analizador
.\analizador.exe      # Windows  (./analizador en Linux/Mac)
```

Al iniciar, el programa lee los catálogos (`equipos.txt` y `posiciones.txt`). Después muestra el menú:

1. **Cargar** `data/jugadores.csv` en la lista doble y en el árbol BST.
2. **Mostrar** en orden de carga (lista hacia adelante), en orden inverso (lista hacia atrás) o alfabético (inorden del árbol).
3. **Ordenar** por goles, asistencias, edad, minutos o nombre, ascendente o descendente, con Bubble Sort o Merge Sort. Muestra cuántas comparaciones hizo.
4. **Filtrar** por equipo, posición o rango de goles.
5. **Buscar** por nombre en la lista o en el árbol, mostrando cuántos pasos tomó.
6. **Información del árbol:** altura, recorridos (preorden, inorden, postorden y por niveles), nivel y ancestros de un jugador.
7. **Top N con el heap:** por goles, asistencias, edad o minutos.
8. **Agregar** un jugador. El equipo y la posición se eligen del catálogo; no se permiten nombres repetidos ni comas.
9. **Actualizar** las 7 estadísticas de un jugador.
10. **Eliminar** un jugador (pide confirmación).
11. **Guardar** los cambios en `data/jugadores.csv`, con respaldo previo.
0. **Salir.** Si hay cambios sin guardar, pregunta si quieres guardarlos.

## 4. SICT0301: Análisis de complejidad

**n** = jugadores, **h** = altura del árbol (la raíz está en el nivel 1), **e** y **p** = número de equipos y de posiciones, **N** = jugadores que pide el Top N.

### Lista doblemente ligada (Avance 2)

| Operación | Mejor | Promedio | Peor | Espacio extra | Uso en el programa |
|---|---|---|---|---|---|
| `insertarAlFinal` | O(1) | O(1) | O(1) | O(1) | Cargar, agregar |
| `buscar` | O(1) | O(n) | O(n) | O(1) | Buscar, actualizar |
| `eliminar` | O(1) | O(n) | O(n) | O(1) | Eliminar |
| `mostrarAdelante`, `mostrarAtras` | O(n) | O(n) | O(n) | O(1) | Mostrar |
| `aVector` | O(n) | O(n) | O(n) | O(n) | Ordenar, filtrar, Top N, guardar, reconstruir el árbol |
| `vaciar` / destructor | O(n) | O(n) | O(n) | O(1) | Recargar, salir |

- Insertar es O(1) gracias al apuntador a la cola.
- `buscar` y `eliminar` recorren desde la cabeza. Una vez encontrado el nodo, quitarlo es O(1), porque conoce a su anterior y a su siguiente.

### Árbol binario de búsqueda (Avance 2)

| Operación | Mejor | Promedio | Peor | Espacio extra | Uso en el programa |
|---|---|---|---|---|---|
| `insertar` | O(1) | O(log n) | O(n) | O(1) | Cargar, agregar, reconstruir (detecta repetidos) |
| `buscar`, `nivelDe` | O(1) | O(log n) | O(n) | O(1) | Buscar, actualizar, eliminar, nivel |
| `ancestros` | O(1) | O(log n) | O(n) | O(h) | Ancestros de un jugador |
| `preorden`, `inorden`, `postorden` | O(n) | O(n) | O(n) | O(h) | Mostrar alfabético, recorridos |
| `porNiveles` (sin cola) | O(n) | O(n log n) | O(n²) | O(h) | Recorrido por niveles |
| `altura` | O(n) | O(n) | O(n) | O(h) | Información del árbol |
| `vaciar` / destructor (postorden) | O(n) | O(n) | O(n) | O(h) | Recargar, reconstruir, salir |

- Cada comparación baja un nivel, así que insertar y buscar cuestan O(h). Con datos en desorden, h ≈ log₂ n; si llegaran ordenados por nombre, h = n.

### Heap máximo (nuevo)

| Operación | Complejidad | Por qué |
|---|---|---|
| `push` | O(log n) | Se agrega al final y sube hasta su lugar (máximo la altura, log₂ n) |
| `pop` | O(log n) | El último pasa a la raíz y baja cambiándose con su hijo mayor |
| `top`, `empty`, `size` | O(1) | El mayor siempre está en la posición 0 del vector |
| Top N completo | O(n log n + N log n) | n `push` y después N `pop`; espacio O(n) |

El heap guarda sus datos en un vector, así que ocupa O(n) de memoria.

### Ordenamientos (Avance 1)

| Algoritmo | Mejor | Promedio | Peor | Espacio |
|---|---|---|---|---|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |

- **Bubble Sort** hace n(n−1)/2 comparaciones. Si una pasada no intercambia nada, termina (mejor caso O(n)).
- **Merge Sort** divide en log₂ n niveles, y en cada nivel `merge` recorre los n elementos con los vectores auxiliares `izquierda` y `derecha`.

### Demás componentes: archivos, validaciones y menú (nuevo)

| Componente | Complejidad | Explicación |
|---|---|---|
| Leer catálogos | O(e + p) | Una pasada por cada archivo |
| Cargar el CSV | O(n·(h + e + p)) | Por línea: revisar catálogos O(e + p), insertar en el árbol O(h) y en la lista O(1) |
| Guardar | O(r + n) | Copiar las r líneas del CSV viejo al respaldo, escribir los n jugadores y volver a contarlos para verificar |
| Agregar | O(h + e + p) | Revisar repetido en el árbol O(h), elegir equipo y posición del catálogo, insertar en árbol O(h) y lista O(1) |
| Actualizar | O(n) | Buscar en la lista O(n) y en el árbol O(h), y reemplazar por medio del apuntador |
| Eliminar | O(n·h) | Eliminar de la lista O(n) y reconstruir el árbol: n inserciones de O(h) |
| Filtros | O(n) | Copiar la lista y recorrerla |
| Validar entradas | O(1) por intento | `leerEntero` revisa el rango; `leerTexto` y `esNumero` recorren el texto (O(longitud)) |
| Menú | O(1) por vuelta | Mostrar opciones y elegir con `switch`; el costo es el de la opción elegida |

### Top N: heap contra ordenar todo con Merge Sort

Ambos cuestan O(n log n) por las n inserciones. Pero el heap solo saca los N que se piden, y Merge Sort ordena a los 300. Medido con los 300 jugadores, por goles:

| Se piden | Heap (`push` + `pop`) | Merge Sort completo |
|---|---:|---:|
| Top 10 | **746** comparaciones | 1,962 comparaciones |
| Los 300 | 3,575 comparaciones | **1,962** comparaciones |

Para un Top pequeño, que es el uso normal, el heap hace menos trabajo. Si se quiere la lista completa, conviene Merge Sort.

### Complejidad de cada opción del menú

| Opción | Uso típico (árbol en desorden, h ≈ log n) | Peor caso |
|---|---|---|
| 1. Cargar | O(n log n) | O(n²) (árbol degenerado) |
| 2. Mostrar | O(n) | O(n) |
| 3. Ordenar | O(n log n) con Merge Sort | O(n²) con Bubble Sort |
| 4. Filtrar | O(n) | O(n) |
| 5. Buscar | Lista O(n), árbol O(log n) | O(n) |
| 6. Info del árbol | O(n) altura y recorridos (por niveles O(n·h)); nivel y ancestros O(log n) | O(n²) (por niveles, degenerado) |
| 7. Top N (heap) | O(n log n) | O(n log n) |
| 8. Agregar | O(log n) | O(n) |
| 9. Actualizar | O(n) | O(n) |
| 10. Eliminar | O(n log n) | O(n²) (reconstruir degenerado) |
| 11. Guardar | O(n) | O(n) |

### Complejidad final del programa

- **Peor caso: O(n²).** Lo dominan Bubble Sort (n(n−1)/2 comparaciones) y las operaciones del árbol si llegara a degenerarse (h = n). En ese caso, cargar, eliminar y el recorrido por niveles hacen n operaciones de O(n).
- **Uso típico: O(n log n).** Con Merge Sort y un árbol en desorden (altura real 18 con 300 jugadores), lo más caro es cargar, ordenar, el Top N y reconstruir el árbol al eliminar. El resto de las opciones son O(n) o menos.
- **Memoria: O(n).** Lista, árbol y las copias en vector que se usan para ordenar, filtrar, el heap y guardar.

### Datos medidos con el CSV real (300 jugadores)

| Medida | Valor |
|---|---|
| Altura del árbol | **18** (mínima posible: 9; peor caso: 300, comprobado insertando los nombres ya ordenados) |
| Pasos para buscar | lista: promedio **150.5**, máximo 300; árbol: promedio **10.4**, máximo 18 |
| Comparaciones al ordenar por goles | Bubble Sort 44,444; Merge Sort 1,962 |

## 5. SICT0302: Selección de estructuras y algoritmos

- **Lista doble:** con el apuntador a la cola, insertar al final es O(1). Con el apuntador `anterior` se muestra al revés y se elimina un nodo sin buscar a su anterior, cosa que en una lista simple no se puede.
- **BST para buscar:** 10 pasos en promedio contra 150 de la lista. El inorden da el orden alfabético sin ordenar, y al insertar detecta nombres repetidos.
- **Templates:** la lista y el árbol sirven para cualquier tipo. Los operadores sobrecargados de `Jugador` (que comparan el nombre) los conectan con la clase.
- **Merge Sort:** el árbol solo ordena por nombre. Para los demás criterios se ordena una copia en O(n log n), contra O(n²) de Bubble Sort, que se queda para comparar.
- **Heap para Top N:** el usuario casi siempre quiere a los primeros N, no la lista completa. El heap da el mayor en O(1) y cada `pop` cuesta O(log n), así que para un Top 10 hace menos de la mitad de comparaciones que ordenar todo.
  - No usa el operador `<` de `Jugador`, porque ese compara por nombre. Compara por el criterio elegido con la función `comparar` de los ordenamientos. Por eso el heap no es template.
- **Reconstruir el árbol al eliminar:** no vimos cómo borrar un nodo de un BST. Por eso se vacía el árbol y se llena otra vez desde la lista: O(n·h) en lugar de O(h), pero instantáneo con 300 jugadores y sin riesgo de que se desincronice.
- **Riesgo del árbol:** si el CSV estuviera ordenado por nombre, el árbol tendría altura 300 y buscar sería O(n). El CSV está agrupado por equipo, así que la altura real es 18.

## 6. SICT0303: Lectura y escritura de archivos

### Lectura (Avance 2)

- **`equipos.txt` y `posiciones.txt`:** se leen al iniciar con `ifstream` y `getline` y se guardan en un `vector<string>`. Si falta alguno o está vacío, el programa avisa y no deja cargar el CSV ni agregar jugadores.
- **`jugadores.csv`:** cada línea se separa por comas con `stringstream`.
  - Se descarta si no tiene 12 campos, si un número es inválido, si el equipo o la posición no están en los catálogos, o si el nombre está repetido.
  - Cada jugador válido se inserta directamente en el árbol y en la lista.
  - Al final se informa cuántas líneas se cargaron y cuántas se descartaron, con el motivo.

### Escritura (nuevo)

- **Formato:** se escribe la lista doble completa en `data/jugadores.csv`, con la **misma cabecera y el mismo orden de columnas** con que se lee. Así el archivo se puede volver a cargar.
- **Respaldo:** antes de sobrescribir, el CSV actual se copia **línea por línea** (`ifstream` → `ofstream`) a `data/jugadores_respaldo.csv`.
- **Verificación y errores:**
  - Si no se puede crear el respaldo o abrir el archivo, se avisa y no se escribe nada.
  - Al terminar se revisa el estado del archivo y se vuelve a abrir para contar los jugadores escritos.
  - Si algo falla, los datos en memoria (lista y árbol) no se tocan, así que no se pierde nada.
  - No se permite guardar una lista vacía, y los nombres no pueden llevar comas porque romperían el CSV.
- **Bandera de cambios sin guardar:** se activa al agregar, actualizar o eliminar, y se apaga al guardar o cargar.
  - El menú muestra "(Hay cambios sin guardar)".
  - Al salir o al recargar el CSV, el programa pregunta antes de perder los cambios.
- **Prueba de ida y vuelta:** cargar → agregar 1, actualizar 1 y eliminar 3 → guardar → cargar en un registro nuevo. Dio los mismos 298 jugadores, con los mismos 12 datos y en el mismo orden. El respaldo quedó idéntico al CSV anterior.

## 7. Casos de prueba

| Entrada | Resultado esperado | Resultado obtenido |
|---|---|---|
| Escribir `hola` en el menú | "Entrada invalida" y vuelve a preguntar | Igual |
| Opciones 2-7 y 9-11 sin cargar | "No hay jugadores. Carga el CSV..." | Igual |
| Falta `equipos.txt` | Aviso al iniciar; no deja cargar ni agregar | Igual |
| Falta `jugadores.csv` | "no se pudo abrir el archivo" | Igual |
| CSV con línea sin campos, número `diez`, equipo o posición inválidos, nombre repetido | Cada línea se descarta con su motivo | Igual |
| Top N con N = 999 | Pide un número entre 1 y 300 | Igual |
| Agregar `Juan, Perez` | Rechaza la coma y pide de nuevo | Igual |
| Agregar un nombre que ya existe | "Ya existe un jugador con ese nombre" | Igual |
| Actualizar o eliminar `Nadie` | "No se encontro a Nadie" | Igual |
| Salir con cambios y elegir "no" | No modifica el CSV | Igual |
| Salir con cambios y elegir "si" | Respalda, guarda y sale | Igual |
| Guardar → volver a cargar | Mismos jugadores y mismos datos | Igual (298 de 298) |
| Eliminar a todos y agregar uno | La lista y el árbol quedan con 1 jugador | Igual |

El programa compila sin errores ni warnings con `g++ -std=c++17 -Wall -Wextra`. Lo probé con AddressSanitizer: **sin fugas de memoria**, porque cada `new` de la lista y del árbol tiene su `delete` en `eliminar`, `vaciar` y los destructores.

### Ejemplo de ejecución real (resumido)

```
Elige una opcion (0-11): 7
--- TOP N POR CRITERIO (HEAP) ---
Elige el criterio (1-4): 1
Cuantos jugadores quieres ver? (1-300): 5
Metiendo los 300 jugadores de la lista doble al heap (push)...
Sacando el Top 5 del heap (top y pop)...
>> Top 5 por goles (quedaron 295 jugadores en el heap)
Erling Haaland          Manchester City   Delantero       25  Noruega             36  35  2738  27   4   2   0   0.89
Igor Thiago             Brentford         Delantero       24  Brasil              36  35  2777  19   3   4   0   0.62
...
Elige una opcion (0-11): 9
Nombre del jugador: Erling Haaland
Buscando en el arbol BST...
...
Goles (0-100): 30
Actualizando el jugador en la lista doble y en el arbol BST...
(Hay cambios sin guardar)
Elige una opcion (0-11): 0
Hay cambios sin guardar. Guardar antes de salir? 1 = si, 2 = no: 1
Respaldando data/jugadores.csv en data/jugadores_respaldo.csv...
Escribiendo la lista doble (300 jugadores) en data/jugadores.csv...
>> Se guardaron 300 jugadores en data/jugadores.csv
Hasta luego!
```

## 8. Estructura de archivos

```
src/
  Jugador.h / Jugador.cpp              Clase Jugador: getters, setters y operadores <, >, ==, <<
  ListaDoble.h                         Template de la lista doblemente ligada
  ArbolBST.h                           Template del árbol binario de búsqueda
  Heap.h                               Heap máximo (MonticuloMax) para el Top N
  Registro.h / Registro.cpp            Lista + árbol + catálogos: cargar, consultar, cambiar y guardar
  Ordenamientos.h / Ordenamientos.cpp  Bubble Sort, Merge Sort y comparar por criterio
  main.cpp                             Menú
data/
  jugadores.csv           Datos de los 300 jugadores (se sobrescribe al guardar)
  jugadores_respaldo.csv  Respaldo que se crea al guardar
  equipos.txt             Catálogo de los 20 equipos
  posiciones.txt          Catálogo de las 4 posiciones
```
