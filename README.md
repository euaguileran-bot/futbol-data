# Analizador de estadísticas — Premier League 2025-2026

**Estructuras de Datos y Algoritmos — Avance 2**

## 1. Descripción del avance

Programa en C++ que carga desde un CSV las estadísticas de **300 jugadores reales de la Premier League 2025-2026** (15 por equipo) y las guarda en dos estructuras programadas a mano:

- **Lista doblemente ligada:** guarda a los jugadores en el orden en que se cargaron.
- **Árbol binario de búsqueda (BST)** ordenado por nombre: sirve para buscar rápido y para obtener el orden alfabético.

Con ellas el programa muestra, ordena (con Bubble Sort o Merge Sort), filtra y busca jugadores, y da información del árbol.

Elegí este tema porque me gusta el fútbol y sigo la Premier League. Además, cada jugador tiene muchos atributos, así que un mismo algoritmo se puede probar con distintos criterios. Las estadísticas del archivo son aproximadas.

**Cambios respecto al Avance 1:**

- **Retroalimentación del profesor:** los equipos y las posiciones ya no están escritos en el código. Se leen al iniciar desde `data/equipos.txt` y `data/posiciones.txt`, y se usan para validar el CSV y para las opciones de los filtros.
- **Estructuras nuevas:** `ListaDoble.h` y `ArbolBST.h`, hechas como templates. `Registro` ya no guarda los jugadores en un vector, sino en la lista y en el árbol.
- **Jugador:** sobrecarga los operadores `<`, `>` y `==`, que comparan el nombre sin importar mayúsculas, y `<<`, que imprime una fila de la tabla. Por eso se quitó `mostrar()`.
- **Menú:** se agregaron buscar e información del árbol.

**Archivos:** `src/` tiene `Jugador`, `ListaDoble.h`, `ArbolBST.h`, `Registro` (estructuras, carga de archivos y consultas), `Ordenamientos` y `main.cpp` (menú). `data/` tiene `jugadores.csv`, `equipos.txt` y `posiciones.txt`.

## 2. Cómo usar el programa

```bash
g++ src/*.cpp -o analizador
.\analizador.exe      # Windows  (./analizador en Linux/Mac)
```

Al iniciar, el programa lee los catálogos. Después muestra el menú:

1. **Cargar** `data/jugadores.csv` en la lista y en el árbol.
2. **Mostrar** en orden de carga (lista hacia adelante), en orden inverso (lista hacia atrás) o en orden alfabético (inorden del árbol).
3. **Ordenar** por goles, asistencias, edad, minutos o nombre, de forma ascendente o descendente, con Bubble Sort o Merge Sort. Muestra cuántas comparaciones hizo.
4. **Filtrar** por equipo, posición o rango de goles.
5. **Buscar** por nombre en la lista o en el árbol. Muestra cuántos pasos tomó.
6. **Información del árbol:** altura, recorridos (preorden, inorden, postorden y por niveles), y el nivel y los ancestros de un jugador.
0. **Salir.**

## 3. Sub-competencias

### SICT0301: Análisis de complejidad

**n** = jugadores, **h** = altura del árbol (la raíz está en el nivel 1), **e** y **p** = número de equipos y de posiciones.

**Lista doblemente ligada**

| Operación | Mejor | Promedio | Peor | Espacio extra | Uso en el programa |
|---|---|---|---|---|---|
| `insertarAlFinal` | O(1) | O(1) | O(1) | O(1) | Cargar el CSV |
| `buscar` | O(1) | O(n) | O(n) | O(1) | Buscar (opción 5) |
| `mostrarAdelante`, `mostrarAtras` | O(n) | O(n) | O(n) | O(1) | Mostrar |
| `aVector` | O(n) | O(n) | O(n) | O(n) | Ordenar y filtrar una copia |
| `vaciar` / destructor | O(n) | O(n) | O(n) | O(1) | Recargar el CSV, salir |

- Insertar es O(1) porque se guarda un apuntador a la cola.
- `buscar` revisa los nodos uno por uno: lo mejor es encontrar al jugador en la cabeza, y lo peor es que no exista.
- La lista ocupa O(n) de memoria: un nodo por jugador.

**Árbol binario de búsqueda**

| Operación | Mejor | Promedio | Peor | Espacio extra | Uso en el programa |
|---|---|---|---|---|---|
| `insertar` | O(1) | O(log n) | O(n) | O(1) | Cargar el CSV (y detectar nombres repetidos) |
| `buscar`, `nivelDe` | O(1) | O(log n) | O(n) | O(1) | Buscar, nivel de un jugador |
| `ancestros` | O(1) | O(log n) | O(n) | O(h) | Ancestros de un jugador |
| `preorden`, `inorden`, `postorden` | O(n) | O(n) | O(n) | O(h) | Mostrar alfabético, recorridos |
| `porNiveles` (sin cola) | O(n) | O(n log n) | O(n²) | O(h) | Recorrido por niveles |
| `altura` | O(n) | O(n) | O(n) | O(h) | Información del árbol |
| `vaciar` / destructor | O(n) | O(n) | O(n) | O(h) | Recargar el CSV, salir |

- Insertar, buscar y las operaciones parecidas bajan un nivel por cada comparación, así que cuestan O(h). Con datos en desorden, h ≈ log₂ n; si llegan ordenados por nombre, h = n.
- Los recorridos visitan cada nodo una vez. La recursión ocupa O(h) de memoria.
- El recorrido por niveles, para cada nivel de 1 a h, recorre el árbol desde la raíz e imprime solo ese nivel, así que cuesta hasta O(n·h).

**Carga de archivos, filtros y ordenamientos**

| Operación | Complejidad | Explicación |
|---|---|---|
| Leer catálogos | O(e + p) | Lee cada línea una vez |
| Cargar el CSV | O(n·(h + e + p)) | Por cada línea: revisar los catálogos (búsqueda secuencial), insertar en el árbol O(h) y en la lista O(1) |
| Filtros | O(n) | Copian la lista a un vector y lo recorren |
| Bubble Sort | O(n) mejor, O(n²) promedio y peor; espacio O(1) | Hace n(n−1)/2 comparaciones; si una pasada no intercambia nada, termina |
| Merge Sort | O(n log n) siempre; espacio O(n) | log₂ n niveles de división, y en cada nivel `merge` recorre los n elementos usando los vectores `izquierda` y `derecha` |

**Datos medidos con el CSV real (300 jugadores)**

| Medida | Valor |
|---|---|
| Altura real del árbol | **18** |
| Altura mínima posible (log₂ 300 ≈ 8.2) | 9 |
| Peor caso (si los jugadores llegaran ordenados por nombre) | 300 (comprobado) |
| Pasos para buscar en la lista | promedio **150.5**, máximo 300 |
| Pasos para buscar en el árbol | promedio **10.4**, máximo 18 |
| Comparaciones al ordenar por goles | Bubble Sort 44,444, Merge Sort 1,962 |

### SICT0302: Selección de las estructuras de datos

- **Lista doble:** con el apuntador a la cola, insertar al final es O(1) y los jugadores quedan en el orden del CSV. Con el apuntador `anterior` también se pueden mostrar al revés, cosa que no se puede en una lista simple.
- **BST para buscar:** buscar en la lista toma 150 pasos en promedio y en el árbol 10. Además, el inorden da el orden alfabético sin ordenar nada, y al insertar se detectan los nombres repetidos.
- **Templates:** la lista y el árbol se escriben una sola vez y sirven para cualquier tipo. Los operadores sobrecargados de `Jugador` son los que conectan la clase con los templates.
- **Merge Sort se sigue usando** porque el árbol solo ordena por nombre. Para ordenar por goles, edad o minutos, se copia la lista a un vector y se ordena esa copia en O(n log n).
- **Riesgo:** si el CSV llegara ordenado por nombre, el árbol se volvería una lista de altura 300 y buscar costaría O(n). El CSV está agrupado por equipo, así que los nombres llegan mezclados y la altura es 18.

### SICT0303: Consultas y lectura de archivos

**Consultas sobre las estructuras:**

- **Lista:** mostrar hacia adelante y hacia atrás, y buscar por nombre.
- **Árbol:** buscar por nombre, orden alfabético, recorridos (preorden, inorden, postorden y por niveles), altura, nivel de un jugador y sus ancestros.
- **Copia de la lista:** ordenar y filtrar.

Las búsquedas muestran los pasos y no distinguen mayúsculas. Para buscar se crea un `Jugador` temporal que solo tiene el nombre.

**Lectura de archivos:**

- **Catálogos** (`equipos.txt`, `posiciones.txt`): se leen con `ifstream` y `getline` antes del menú y se guardan en un `vector<string>`. Si falta alguno o está vacío, el programa lo avisa y no deja cargar el CSV.
- **`jugadores.csv`:** cada línea se separa por comas con `stringstream`.
  - Se descarta si no tiene 12 campos, si un número es inválido, si el equipo o la posición no están en los catálogos, o si el nombre está repetido.
  - Cada jugador válido se inserta directamente en el árbol y en la lista.
  - Al final se informa cuántas líneas se cargaron y cuántas se descartaron, con el motivo.
