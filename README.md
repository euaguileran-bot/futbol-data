# Analizador de estadísticas — Premier League 2025-2026

**Estructuras de Datos y Algoritmos — Avance 2**

## 1. Descripción del avance

Programa en C++ que carga desde un CSV las estadísticas de **300 jugadores reales de la Premier League 2025-2026** (15 por equipo) y los guarda en dos estructuras de datos programadas a mano:

- Una **lista doblemente ligada**, que es el almacenamiento principal, en el orden en que se cargaron. Ahí se agregan, actualizan y eliminan jugadores.
- Un **árbol binario de búsqueda (BST)** ordenado por nombre. Sirve como índice para buscar rápido y para obtener el orden alfabético con un recorrido inorden.

Con esas estructuras el programa permite mostrar, ordenar (Bubble Sort o Merge Sort), filtrar, buscar, agregar, actualizar y eliminar jugadores, y consultar información del árbol.

Elegí este tema porque me gusta el fútbol y sigo la Premier League. Además, cada jugador tiene muchos atributos, así que un mismo algoritmo se puede probar con distintos criterios. Las estadísticas del archivo son aproximadas.

### Cambios respecto al Avance 1

- **Retroalimentación del profesor:** los equipos y las posiciones ya no están escritos en el código. Se leen al iniciar el programa desde `data/equipos.txt` y `data/posiciones.txt`. Se usan para validar el CSV, para elegir equipo y posición al agregar un jugador y para mostrar las opciones de los filtros. Los límites para validar números (edad de 15 a 50, 38 partidos por temporada, etc.) se dejaron como constantes en `main.cpp`, porque son reglas del programa y no catálogos de datos.
- **Estructuras nuevas:** `ListaDoble.h` y `ArbolBST.h`, hechas como templates. `Registro` ya no usa un vector: guarda la lista y el árbol y los mantiene sincronizados.
- **Jugador:** tiene setters para las estadísticas y sobrecarga los operadores `<`, `>`, `==` (que comparan el nombre sin importar mayúsculas) y `<<` (que imprime una fila de la tabla).
- **Menú nuevo:** se agregaron buscar, agregar, actualizar, eliminar e información del árbol.
- **Ordenar por nombre** ahora usa los operadores de `Jugador`, para que el orden sea igual al del árbol.
- **Se quitaron** `Jugador::mostrar()`, que reemplaza el operador `<<`, y `Registro::mostrarTodos()`, que reemplazan las 3 formas de mostrar.

### Estructura de archivos

```
src/
  Jugador.h / Jugador.cpp              Clase Jugador, setters y operadores
  ListaDoble.h                         Template de la lista doblemente ligada
  ArbolBST.h                           Template del árbol binario de búsqueda
  Registro.h / Registro.cpp            Lista + árbol + catálogos, carga de archivos, consultas y cambios
  Ordenamientos.h / Ordenamientos.cpp  Bubble Sort y Merge Sort (del Avance 1)
  main.cpp                             Menú
data/
  jugadores.csv   equipos.txt   posiciones.txt
```

## 2. Cómo usar el programa

Desde la carpeta del proyecto:

```bash
g++ src/*.cpp -o analizador
.\analizador.exe      # Windows  (./analizador en Linux/Mac)
```

Al iniciar, el programa lee `equipos.txt` y `posiciones.txt`. Después muestra el menú:

1. **Cargar** los jugadores de `data/jugadores.csv` en la lista y en el árbol.
2. **Mostrar:** en orden de carga (lista hacia adelante), en orden inverso (lista hacia atrás) o alfabético (inorden del árbol).
3. **Ordenar** por goles, asistencias, edad, minutos o nombre, de forma ascendente o descendente, con Bubble Sort o Merge Sort. Muestra cuántas comparaciones hizo.
4. **Filtrar** por equipo, posición o rango de goles.
5. **Buscar** por nombre en la lista, en el árbol o en los dos, y muestra los pasos de cada búsqueda.
6. **Agregar** un jugador (al inicio o al final de la lista). No permite nombres repetidos.
7. **Actualizar** las estadísticas de un jugador.
8. **Eliminar** un jugador.
9. **Información del árbol:** altura, recorridos (preorden, inorden, postorden y por niveles), y el nivel y los ancestros de un jugador.
0. **Salir.**

Todas las entradas se validan. Si no hay jugadores, cada opción lo avisa.

Ejemplo real (resumido):

```
>> Catalogos cargados: 20 equipos y 4 posiciones
Elige una opcion (0-9): 1
Lineas cargadas: 300 | Lineas descartadas: 0
>> Se cargaron 300 jugadores en la lista y 300 en el arbol
Elige una opcion (0-9): 5
Nombre completo sin acentos (ej. Declan Rice): Erling Haaland
Elige (1-3): 3
>> Lista: encontrado en la posicion 193 (194 pasos)
>> Arbol: encontrado (12 pasos)
Elige una opcion (0-9): 9
Altura del arbol: 18 niveles (la raiz es el nivel 1)
Elige (0-5): 5
Nombre del jugador: Erling Haaland
>> Esta en el nivel 12 del arbol
>> Ancestros (de la raiz hasta su padre):
(tabla con 11 jugadores, empezando por la raiz: David Raya)
```

## 3. Sub-competencias

### SICT0301: Análisis de complejidad

**n** = número de jugadores, **h** = altura del árbol, **e** y **p** = número de equipos y de posiciones en los catálogos. La raíz del árbol está en el **nivel 1**, y la altura es el número de niveles.

#### Lista doblemente ligada

| Operación | Mejor | Promedio | Peor | Espacio extra | Dónde se usa |
|---|---|---|---|---|---|
| `insertarAlFinal`, `insertarAlInicio` | O(1) | O(1) | O(1) | O(1) | Cargar CSV, agregar |
| `buscar` (secuencial) | O(1) | O(n) | O(n) | O(1) | Buscar, actualizar, eliminar |
| `obtenerEnPosicion`, `actualizarEnPosicion`, `eliminarEnPosicion` | O(1) | O(n) | O(n) | O(1) | Buscar, actualizar, eliminar |
| `mostrarAdelante`, `mostrarAtras` | O(n) | O(n) | O(n) | O(1) | Mostrar |
| `aVector` | O(n) | O(n) | O(n) | O(n) | Ordenar, filtrar, reconstruir el árbol |
| `vaciar` / destructor | O(n) | O(n) | O(n) | O(1) | Recargar el CSV, salir |

- Insertar es O(1) porque la lista guarda apuntadores a la cabeza y a la cola, así que no hay que recorrerla.
- `buscar` revisa los nodos uno por uno: lo mejor es que el jugador esté en la cabeza, y lo peor es que no exista (n pasos).
- Para llegar a una posición, la lista empieza por la punta más cercana (la cabeza o la cola). Así recorre como máximo n/2 nodos, que sigue siendo O(n).
- La lista ocupa O(n) de memoria: un nodo por jugador, con dos apuntadores cada uno.

#### Árbol binario de búsqueda

| Operación | Mejor | Promedio | Peor | Espacio extra | Dónde se usa |
|---|---|---|---|---|---|
| `insertar` | O(1) | O(log n) | O(n) | O(1) | Cargar CSV, agregar, reconstruir |
| `buscar`, `actualizar`, `nivelDe` | O(1) | O(log n) | O(n) | O(1) | Buscar, actualizar, eliminar, nivel |
| `ancestros` | O(1) | O(log n) | O(n) | O(h) | Ancestros de un jugador |
| `preorden`, `inorden`, `postorden`, `inordenAVector` | O(n) | O(n) | O(n) | O(h) | Mostrar alfabético, recorridos |
| `porNiveles` (sin cola) | O(n) | O(n log n) | O(n²) | O(h) | Recorrido por niveles |
| `altura`, `contarNodos` | O(n) | O(n) | O(n) | O(h) | Información del árbol |
| `vaciar` / destructor (en postorden) | O(n) | O(n) | O(n) | O(h) | Recargar, reconstruir, salir |

- Buscar, insertar y las demás operaciones de ese tipo bajan un nivel por cada comparación, así que cuestan O(h). Si el árbol está balanceado, h ≈ log₂ n. Si los datos llegan ordenados, el árbol se vuelve una lista y h = n.
- El mejor caso es encontrar al jugador en la raíz, con una sola comparación.
- Los recorridos visitan cada nodo una vez, así que son O(n). La recursión ocupa O(h) en la pila de llamadas.
- **Por niveles sin cola:** para cada nivel de 1 a h, se recorre el árbol desde la raíz y solo se imprimen los nodos de ese nivel. Por eso cuesta O(n·h).

#### Operaciones del programa (Registro)

| Operación | Complejidad | Explicación |
|---|---|---|
| Cargar catálogos | O(e + p) | Lee cada línea una vez |
| Cargar CSV | O(n·(h + e + p)) | Por línea: revisar los catálogos (búsqueda secuencial), insertar en el árbol O(h) y en la lista O(1). En promedio O(n log n), en el peor caso O(n²) |
| Agregar | O(h) | Inserta en el árbol, que detecta los repetidos, y en la lista en O(1) |
| Actualizar | O(n) | Busca en la lista O(n), la actualiza y actualiza el árbol O(h) |
| Eliminar | O(n·h) | Elimina de la lista O(n) y reconstruye el árbol: n inserciones de O(h) |
| Filtros | O(n) | Copian la lista a un vector y lo recorren |
| Ordenar | O(n) + el algoritmo | Copian la lista a un vector y ordenan la copia |

#### Ordenamientos (del Avance 1)

| Algoritmo | Mejor caso | Promedio | Peor caso | Espacio |
|---|---|---|---|---|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |

- **Bubble Sort:** compara cada par de vecinos. Hace n(n−1)/2 comparaciones, que con n = 300 son 44,850. Si en una pasada no hay intercambios, termina (mejor caso O(n)). Ordena en el mismo vector, así que su espacio es O(1).
- **Merge Sort:** siempre divide a la mitad, así que hay log₂ n niveles, y en cada nivel `merge` recorre los n elementos: O(n log n). Usa los vectores auxiliares `izquierda` y `derecha`, así que su espacio es O(n).
- Medido al ordenar los 300 jugadores por goles: Bubble Sort hizo **44,444** comparaciones y Merge Sort **1,962**.

#### Datos medidos con el CSV real (300 jugadores)

| Medida | Valor |
|---|---|
| Altura real del árbol | **18** |
| Altura mínima posible (log₂ 300 ≈ 8.2) | 9 |
| Peor caso (si los jugadores llegaran ordenados por nombre) | 300 (lo comprobé) |
| Pasos para encontrar a un jugador en la **lista** | promedio **150.5**, máximo 300 |
| Pasos para encontrar a un jugador en el **árbol** | promedio **10.4**, máximo 18 |

El árbol real no queda perfectamente balanceado (18 contra 9), pero está muy lejos del peor caso. Encontrar a un jugador cuesta unas 15 veces menos pasos que en la lista.

### SICT0302: Selección de las estructuras de datos

- **¿Por qué lista doble y no simple?** Con el apuntador a la cola, insertar al final es O(1), y así se cargan los 300 jugadores del CSV. Con el apuntador `anterior` se puede mostrar en orden inverso, y para eliminar o actualizar se llega a la posición desde la punta más cercana (máximo n/2 pasos). En una lista simple siempre habría que empezar desde la cabeza.
- **¿Por qué un BST para buscar?** Buscar en la lista es O(n), con 150 pasos en promedio. En el árbol es O(h), con 10 pasos en promedio. Además, el recorrido inorden da el orden alfabético sin tener que ordenar, y al insertar el árbol detecta nombres repetidos.
- **¿Por qué templates?** La lista y el árbol se escriben una sola vez y sirven para cualquier tipo. Los probé con `int` y los uso con `Jugador`. Lo que los conecta con `Jugador` son los operadores sobrecargados.
- **¿Por qué se sigue necesitando Merge Sort?** El árbol solo ordena por nombre. Para ordenar por goles, edad o minutos se copia la lista a un vector y se ordena esa copia con Merge Sort, que es O(n log n).
- **¿Por qué reconstruir el árbol al eliminar?** Todavía no hemos visto cómo eliminar un nodo de un BST. Por eso, al eliminar un jugador de la lista, se vacía el árbol y se vuelve a llenar desde la lista. Cuesta O(n·h) en lugar de O(h), pero con 300 jugadores es instantáneo y el árbol nunca queda desincronizado. Como se inserta en el orden de la lista, la raíz pasa a ser el primer jugador de la lista.
- **Riesgo del árbol:** si los jugadores llegaran ordenados por nombre, cada uno quedaría a la derecha del anterior. El árbol se volvería una lista de altura 300 y buscar costaría O(n), igual que en la lista. El CSV está agrupado por equipo, así que los nombres llegan mezclados y la altura es 18. Por eso **no conviene ordenar el CSV por nombre antes de cargarlo**.
- **Costo de memoria:** cada jugador está guardado dos veces, en la lista y en el árbol. Son O(n) de memoria extra, y por eso cada cambio actualiza las dos estructuras.

### SICT0303: Consultas y lectura de archivos

**Consultas implementadas sobre las estructuras:**

- **Lista:**
  - Mostrar hacia adelante y hacia atrás.
  - Buscar por nombre, mostrando la posición y los pasos.
  - Copia a un vector para ordenar (5 criterios, con Bubble Sort o Merge Sort) y para filtrar (por equipo, posición o rango de goles).
- **Árbol:**
  - Buscar por nombre, mostrando los pasos.
  - Orden alfabético (inorden).
  - Recorridos preorden, postorden y por niveles.
  - Altura.
  - Nivel de un jugador.
  - Ancestros de un jugador (el camino desde la raíz).
- **Buscar en las dos a la vez** para comparar los pasos.
- **Para buscar se crea un `Jugador` temporal que solo tiene el nombre.** Como los operadores comparan solo el nombre, eso basta. Además, la búsqueda no distingue mayúsculas.

**Lectura de archivos hacia las estructuras:**

- **`equipos.txt` y `posiciones.txt`** se leen al iniciar con `ifstream` y `getline`, y se guardan en un `vector<string>` cada uno.
  - Se quita el `\r` de los archivos de Windows y se ignoran las líneas vacías.
  - Si falta un archivo o está vacío, el programa lo avisa y sigue funcionando, pero no deja cargar el CSV ni agregar jugadores, porque no puede validarlos.
- **`jugadores.csv`** se lee línea por línea, y cada línea se separa por comas con `stringstream`.
  - Se descarta la línea si no tiene 12 campos, si un número es inválido, si el equipo o la posición no están en los catálogos, o si el nombre ya existe.
  - Cada jugador válido se inserta **directamente** en el árbol, que detecta los repetidos, y después al final de la lista, sin vector intermedio.
  - Al terminar se informa cuántas líneas se cargaron, cuántas se descartaron y por qué.
  - Si el CSV no existe, se avisa.
  - Al volver a cargar, se vacían las dos estructuras para no duplicar jugadores.
