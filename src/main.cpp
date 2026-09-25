// main.cpp
// Menú principal del Analizador de estadísticas de la Premier League 2025-2026.
//
// Compilar:  g++ src/*.cpp -o analizador
// Ejecutar:  ./analizador   (desde la carpeta principal del proyecto)

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>   // exit

#include "Jugador.h"
#include "Registro.h"
#include "Ordenamientos.h"
#include "Busquedas.h"
#include "Utilidades.h"

using namespace std;

const string RUTA_POR_DEFECTO = "data/jugadores.csv";
const string RUTA_EXPORTAR_POR_DEFECTO = "data/resultado.csv";

// Agrupa lo que el programa necesita "recordar" entre una opción del menú y otra.
// El "resultado actual" es la última lista que se mostró, ordenó o filtró:
// es la que se ordena (opción 3), en la que se busca (opción 6) y la que se
// exporta (opción 7).
struct EstadoPrograma {
    vector<Jugador> resultadoActual;
    string origen;            // de dónde salió, ej. "todos los jugadores" o "filtro: equipo = Arsenal"
    string orden;             // cómo está ordenado, ej. "original del CSV" o "goles (descendente)"
    bool ordenadoPorNombre;   // true solo si está ordenado por nombre A-Z (lo pide la búsqueda binaria)
    string rutaCargada;       // archivo del que se cargaron los datos
};

// =================== Lectura segura de datos del usuario ===================

// Lee una línea completa del teclado (sin espacios al inicio y al final).
// Se usa getline en lugar de "cin >> numero" porque, si el usuario escribe una
// letra donde va un número, cin queda en estado de error y el programa puede
// entrar en un ciclo infinito. Con getline siempre leemos texto y después
// nosotros revisamos si es un número válido.
string leerLinea() {
    string linea;
    if (!getline(cin, linea)) {
        // Se terminó la entrada (Ctrl+D en Linux/Mac, Ctrl+Z en Windows)
        cout << endl << "Fin de la entrada. Saliendo del programa." << endl;
        exit(0);
    }
    return limpiarEspacios(linea);
}

// Pide un número entero y no deja avanzar hasta que esté entre minimo y maximo
int leerEntero(const string& mensaje, int minimo, int maximo) {
    while (true) {
        cout << mensaje;
        string texto = leerLinea();
        int numero;
        if (convertirAEntero(texto, numero) && numero >= minimo && numero <= maximo) {
            return numero;
        }
        cout << "  Entrada invalida. Escribe un numero entero entre "
             << minimo << " y " << maximo << "." << endl;
    }
}

// Pide una letra y solo acepta una de las dos opciones (ej. 'a'/'b' o 's'/'n')
char leerLetra(const string& mensaje, char opcion1, char opcion2) {
    while (true) {
        cout << mensaje;
        string texto = aMinusculas(leerLinea());
        if (texto.size() == 1 && (texto[0] == opcion1 || texto[0] == opcion2)) {
            return texto[0];
        }
        cout << "  Entrada invalida. Escribe '" << opcion1 << "' o '" << opcion2 << "'." << endl;
    }
}

// Pide un texto y no deja avanzar si el usuario solo presiona Enter
string leerTextoNoVacio(const string& mensaje) {
    while (true) {
        cout << mensaje;
        string texto = leerLinea();
        if (!texto.empty()) {
            return texto;
        }
        cout << "  El texto no puede quedar vacio." << endl;
    }
}

// Muestra una lista numerada (en 3 columnas) y regresa el texto elegido.
// Así el usuario elige con un número y no hay errores de escritura.
string elegirDeLista(const string& titulo, const vector<string>& opciones) {
    cout << titulo << endl;
    int n = opciones.size();
    for (int i = 0; i < n; i++) {
        cout << "  " << right << setw(2) << i + 1 << ". " << left << setw(22) << opciones[i];
        if ((i + 1) % 3 == 0 || i == n - 1) {
            cout << endl;   // salto de línea cada 3 opciones
        }
    }
    int eleccion = leerEntero("Elige una opcion (1-" + to_string(n) + "): ", 1, n);
    return opciones[eleccion - 1];
}

// ============================ Funciones auxiliares ============================

// Regresa, sin repetir y en orden alfabético, los equipos (campo 10) o las
// nacionalidades (campo 11) que aparecen en la lista. Se usa la misma
// numeración que los criterios de ordenamiento.
vector<string> obtenerValoresUnicos(const vector<Jugador>& lista, int campo) {
    vector<string> valores;
    int n = lista.size();

    for (int i = 0; i < n; i++) {
        string valor;
        if (campo == 10) {
            valor = lista[i].getEquipo();
        } else {
            valor = lista[i].getNacionalidad();
        }

        // Búsqueda secuencial para no agregar el mismo valor dos veces
        bool yaExiste = false;
        int m = valores.size();
        for (int j = 0; j < m && !yaExiste; j++) {
            if (valores[j] == valor) {
                yaExiste = true;
            }
        }
        if (!yaExiste) {
            valores.push_back(valor);
        }
    }

    // Selection sort para mostrar los valores en orden alfabético
    int m = valores.size();
    for (int i = 0; i < m - 1; i++) {
        int indiceMenor = i;
        for (int j = i + 1; j < m; j++) {
            if (valores[j] < valores[indiceMenor]) {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) {
            string temporal = valores[i];
            valores[i] = valores[indiceMenor];
            valores[indiceMenor] = temporal;
        }
    }
    return valores;
}

// Texto que describe un orden, ej. "goles (descendente)"
string describirOrden(int criterio, bool ascendente) {
    if (ascendente) {
        return nombreCriterio(criterio) + " (ascendente)";
    }
    return nombreCriterio(criterio) + " (descendente)";
}

// Indica si la ruta termina en ".csv" (sin importar mayúsculas)
bool terminaEnCsv(const string& ruta) {
    int n = ruta.size();
    return n >= 4 && aMinusculas(ruta.substr(n - 4)) == ".csv";
}

// Hace que el resultado actual vuelva a ser la lista completa del registro
void usarTodosLosJugadores(const Registro& registro, EstadoPrograma& estado) {
    estado.resultadoActual = registro.getJugadores();
    estado.origen = "todos los jugadores";
    estado.orden = "original del CSV";
    estado.ordenadoPorNombre = false;
}

// ============================ Opciones del menú ============================

void mostrarMenu(const Registro& registro, const EstadoPrograma& estado) {
    cout << endl;
    cout << "==== ANALIZADOR PREMIER LEAGUE ====" << endl;
    if (registro.getCantidad() == 0) {
        cout << "(Aun no hay jugadores cargados)" << endl;
    } else {
        cout << "Jugadores cargados: " << registro.getCantidad()
             << "  (" << estado.rutaCargada << ")" << endl;
        cout << "Resultado actual:   " << estado.resultadoActual.size() << " jugadores | "
             << estado.origen << " | orden: " << estado.orden << endl;
    }
    cout << "-----------------------------------" << endl;
    cout << "1. Cargar jugadores desde CSV" << endl;
    cout << "2. Mostrar todos los jugadores" << endl;
    cout << "3. Ordenar jugadores" << endl;
    cout << "4. Mostrar Top N goleadores" << endl;
    cout << "5. Filtrar jugadores" << endl;
    cout << "6. Buscar jugador por nombre" << endl;
    cout << "7. Exportar resultado actual a nuevo CSV" << endl;
    cout << "0. Salir" << endl;
}

// Opción 1
void opcionCargar(Registro& registro, EstadoPrograma& estado) {
    cout << endl << "--- CARGAR JUGADORES ---" << endl;
    cout << "Ruta del archivo (Enter = " << RUTA_POR_DEFECTO << "): ";
    string ruta = leerLinea();
    if (ruta.empty()) {
        ruta = RUTA_POR_DEFECTO;
    }

    int cantidad = registro.cargarDesdeCSV(ruta);
    if (cantidad > 0) {
        estado.rutaCargada = ruta;
        usarTodosLosJugadores(registro, estado);
        cout << ">> Se cargaron " << cantidad << " jugadores desde \"" << ruta << "\"." << endl;
    } else if (registro.getCantidad() > 0) {
        cout << "Se conservan los " << registro.getCantidad()
             << " jugadores que ya estaban cargados." << endl;
    }
}

// Opción 2
void opcionMostrarTodos(const Registro& registro, EstadoPrograma& estado) {
    cout << endl << "--- TODOS LOS JUGADORES ---" << endl;
    registro.mostrarTodos();
    usarTodosLosJugadores(registro, estado);
    cout << "(El resultado actual vuelve a ser la lista completa de jugadores.)" << endl;
}

// Opción 3
void opcionOrdenar(const Registro& registro, EstadoPrograma& estado) {
    int cantidad = estado.resultadoActual.size();
    cout << endl << "--- ORDENAR JUGADORES ---" << endl;
    cout << "Se ordenara el resultado actual (" << cantidad << " jugadores: "
         << estado.origen << ")." << endl;

    cout << "Criterios:" << endl;
    cout << "   1 = goles               7 = tarjetas amarillas" << endl;
    cout << "   2 = asistencias         8 = tarjetas rojas" << endl;
    cout << "   3 = edad                9 = nombre (alfabetico)" << endl;
    cout << "   4 = minutos            10 = equipo (alfabetico)" << endl;
    cout << "   5 = partidos jugados   11 = nacionalidad (alfabetico)" << endl;
    cout << "   6 = partidos titular" << endl;
    int criterio = leerEntero("Elige el criterio (1-11): ", 1, 11);

    cout << "Orden:" << endl;
    cout << "   1 = Ascendente  (menor a mayor / A-Z)" << endl;
    cout << "   2 = Descendente (mayor a menor / Z-A)" << endl;
    bool ascendente = (leerEntero("Elige el orden (1-2): ", 1, 2) == 1);

    cout << "Algoritmo:" << endl;
    cout << "   a) Bubble Sort" << endl;
    cout << "   b) Merge Sort" << endl;
    char algoritmo = leerLetra("Elige el algoritmo (a/b): ", 'a', 'b');

    string nombreAlgoritmo;
    if (algoritmo == 'a') {
        bubbleSort(estado.resultadoActual, criterio, ascendente);
        nombreAlgoritmo = "Bubble Sort";
    } else {
        mergeSort(estado.resultadoActual, criterio, ascendente);
        nombreAlgoritmo = "Merge Sort";
    }

    estado.orden = describirOrden(criterio, ascendente);
    // La búsqueda binaria solo funciona si quedó ordenado por nombre de A a Z
    estado.ordenadoPorNombre = (criterio == 9 && ascendente);

    cout << endl << ">> Algoritmo usado: " << nombreAlgoritmo
         << " | Jugadores procesados: " << cantidad
         << " | Criterio: " << estado.orden << endl;

    int limite = leerEntero("Cuantos jugadores quieres ver? (0 = todos): ", 0, cantidad);
    registro.mostrarLista(estado.resultadoActual, limite);
    cout << ">> Ordenado con " << nombreAlgoritmo << ": " << cantidad
         << " jugadores procesados por " << estado.orden << "." << endl;
}

// Opción 4
void opcionTopGoleadores(const Registro& registro, EstadoPrograma& estado) {
    int total = registro.getCantidad();
    cout << endl << "--- TOP N GOLEADORES ---" << endl;
    int n = leerEntero("Cuantos goleadores quieres ver? (1-" + to_string(total) + "): ", 1, total);

    // Se ordena una COPIA de todos los jugadores para no alterar el registro
    vector<Jugador> copia = registro.getJugadores();
    mergeSort(copia, 1, false);   // criterio 1 = goles, false = descendente

    vector<Jugador> top;
    for (int i = 0; i < n; i++) {
        top.push_back(copia[i]);
    }

    estado.resultadoActual = top;
    estado.origen = "Top " + to_string(n) + " goleadores";
    estado.orden = "goles (descendente)";
    estado.ordenadoPorNombre = false;

    cout << ">> Algoritmo usado: Merge Sort | Jugadores procesados: " << total
         << " | Criterio: goles (descendente)" << endl;
    registro.mostrarLista(top, 0);
}

// Opción 5
void opcionFiltrar(const Registro& registro, EstadoPrograma& estado) {
    cout << endl << "--- FILTRAR JUGADORES ---" << endl;
    cout << "(Los filtros se aplican sobre todos los jugadores cargados)" << endl;
    cout << "   1. Por equipo" << endl;
    cout << "   2. Por posicion" << endl;
    cout << "   3. Por nacionalidad" << endl;
    cout << "   4. Por rango de goles" << endl;
    cout << "   5. Por rango de asistencias" << endl;
    cout << "   6. Por rango de edad" << endl;
    cout << "   7. Por rango de minutos" << endl;
    cout << "   0. Volver al menu principal" << endl;
    int tipo = leerEntero("Elige el tipo de filtro (0-7): ", 0, 7);
    if (tipo == 0) {
        return;
    }

    vector<Jugador> resultado;
    string descripcion;

    if (tipo == 1) {
        vector<string> equipos = obtenerValoresUnicos(registro.getJugadores(), 10);
        string equipo = elegirDeLista("Equipos:", equipos);
        resultado = registro.filtrarPorEquipo(equipo);
        descripcion = "filtro: equipo = " + equipo;
    } else if (tipo == 2) {
        vector<string> posiciones = {"Portero", "Defensa", "Mediocampista", "Delantero"};
        string posicion = elegirDeLista("Posiciones:", posiciones);
        resultado = registro.filtrarPorPosicion(posicion);
        descripcion = "filtro: posicion = " + posicion;
    } else if (tipo == 3) {
        vector<string> nacionalidades = obtenerValoresUnicos(registro.getJugadores(), 11);
        string nacionalidad = elegirDeLista("Nacionalidades:", nacionalidades);
        resultado = registro.filtrarPorNacionalidad(nacionalidad);
        descripcion = "filtro: nacionalidad = " + nacionalidad;
    } else {
        // Filtros por rango numérico (tipos 4 a 7)
        string campo;
        if (tipo == 4) {
            campo = "goles";
        } else if (tipo == 5) {
            campo = "asistencias";
        } else if (tipo == 6) {
            campo = "edad";
        } else {
            campo = "minutos";
        }

        int minimo = leerEntero("Valor minimo de " + campo + ": ", 0, 99999);
        // El máximo no puede ser menor que el mínimo
        int maximo = leerEntero("Valor maximo de " + campo + ": ", minimo, 99999);

        switch (tipo) {
            case 4: resultado = registro.filtrarPorRangoGoles(minimo, maximo); break;
            case 5: resultado = registro.filtrarPorRangoAsistencias(minimo, maximo); break;
            case 6: resultado = registro.filtrarPorRangoEdad(minimo, maximo); break;
            case 7: resultado = registro.filtrarPorRangoMinutos(minimo, maximo); break;
        }
        descripcion = "filtro: " + campo + " entre " + to_string(minimo) + " y " + to_string(maximo);
    }

    if (resultado.empty()) {
        cout << ">> Ningun jugador cumple el filtro (" << descripcion
             << "). El resultado actual no cambia." << endl;
        return;
    }

    estado.resultadoActual = resultado;
    estado.origen = descripcion;
    estado.orden = "original del CSV";
    estado.ordenadoPorNombre = false;

    registro.mostrarLista(resultado, 0);
    cout << ">> " << resultado.size() << " jugadores cumplen el filtro (" << descripcion << ")." << endl;
}

// Opción 6
void opcionBuscar(const Registro& registro, EstadoPrograma& estado) {
    int cantidad = estado.resultadoActual.size();
    cout << endl << "--- BUSCAR JUGADOR POR NOMBRE ---" << endl;
    cout << "Se buscara en el resultado actual (" << cantidad << " jugadores: "
         << estado.origen << ")." << endl;
    cout << "Escribe el nombre completo sin acentos (ej. Mohamed Salah, Martin Odegaard)." << endl;
    string nombre = leerTextoNoVacio("Nombre: ");

    cout << "Metodo de busqueda:" << endl;
    cout << "   a) Busqueda secuencial" << endl;
    cout << "   b) Busqueda binaria (requiere datos ordenados por nombre A-Z)" << endl;
    char metodo = leerLetra("Elige el metodo (a/b): ", 'a', 'b');

    int indice;
    string nombreMetodo;
    if (metodo == 'a') {
        indice = busquedaSecuencial(estado.resultadoActual, nombre);
        nombreMetodo = "Busqueda secuencial";
    } else {
        // La búsqueda binaria descarta la mitad de los datos en cada paso
        // suponiendo que están en orden alfabético. Si no lo están, podría
        // descartar justo la mitad donde está el jugador, por eso lo verificamos.
        if (!estado.ordenadoPorNombre) {
            cout << "  Aviso: la busqueda binaria requiere que los datos esten ordenados por nombre (A-Z)." << endl;
            cout << "  El resultado actual esta ordenado por: " << estado.orden << "." << endl;
            char respuesta = leerLetra("  Ordenarlo ahora por nombre con Merge Sort? (s/n): ", 's', 'n');
            if (respuesta == 'n') {
                cout << "Busqueda cancelada. Tambien puedes usar la opcion 3 (criterio 9, ascendente)." << endl;
                return;
            }
            mergeSort(estado.resultadoActual, 9, true);
            estado.orden = "nombre (ascendente)";
            estado.ordenadoPorNombre = true;
            cout << ">> Algoritmo usado: Merge Sort | Jugadores procesados: " << cantidad
                 << " | Criterio: nombre (ascendente)" << endl;
        }
        indice = busquedaBinaria(estado.resultadoActual, nombre);
        nombreMetodo = "Busqueda binaria";
    }

    if (indice == -1) {
        cout << ">> " << nombreMetodo << ": no se encontro a \"" << nombre
             << "\" en el resultado actual." << endl;
        cout << "   Revisa que el nombre este completo y sin acentos. Si aplicaste un filtro," << endl;
        cout << "   usa la opcion 2 para volver a trabajar con todos los jugadores." << endl;
    } else {
        cout << ">> " << nombreMetodo << ": jugador encontrado en el indice " << indice
             << " del resultado actual." << endl;
        vector<Jugador> encontrado;
        encontrado.push_back(estado.resultadoActual[indice]);
        registro.mostrarLista(encontrado, 0);
    }
}

// Opción 7
void opcionExportar(const Registro& registro, const EstadoPrograma& estado) {
    cout << endl << "--- EXPORTAR RESULTADO ACTUAL ---" << endl;
    cout << "Se exportaran " << estado.resultadoActual.size() << " jugadores ("
         << estado.origen << ", orden: " << estado.orden << ")." << endl;
    cout << "Ruta del nuevo archivo (Enter = " << RUTA_EXPORTAR_POR_DEFECTO << "): ";
    string ruta = leerLinea();
    if (ruta.empty()) {
        ruta = RUTA_EXPORTAR_POR_DEFECTO;
    }
    if (!terminaEnCsv(ruta)) {
        ruta = ruta + ".csv";   // agregamos la extensión si no la escribió
    }

    // Protección para no borrar por accidente el archivo con los datos originales
    if (aMinusculas(ruta) == aMinusculas(estado.rutaCargada)) {
        cout << "  Error: no se puede sobrescribir el archivo de datos original. Usa otro nombre." << endl;
        return;
    }

    if (registro.exportarACSV(ruta, estado.resultadoActual)) {
        cout << ">> Se exportaron " << estado.resultadoActual.size()
             << " jugadores a \"" << ruta << "\"." << endl;
    } else {
        cout << "  Error: no se pudo crear el archivo \"" << ruta
             << "\". Revisa que la carpeta exista." << endl;
    }
}

// ================================== main ==================================

int main() {
    Registro registro;
    EstadoPrograma estado;
    estado.ordenadoPorNombre = false;

    int opcion = -1;
    while (opcion != 0) {
        mostrarMenu(registro, estado);
        opcion = leerEntero("Elige una opcion (0-7): ", 0, 7);

        // Las opciones 2 a 7 necesitan que ya haya jugadores cargados
        if (opcion >= 2 && registro.getCantidad() == 0) {
            cout << "  Primero carga los jugadores con la opcion 1." << endl;
            continue;
        }

        switch (opcion) {
            case 1: opcionCargar(registro, estado); break;
            case 2: opcionMostrarTodos(registro, estado); break;
            case 3: opcionOrdenar(registro, estado); break;
            case 4: opcionTopGoleadores(registro, estado); break;
            case 5: opcionFiltrar(registro, estado); break;
            case 6: opcionBuscar(registro, estado); break;
            case 7: opcionExportar(registro, estado); break;
            case 0: cout << "Gracias por usar el analizador. Hasta luego!" << endl; break;
        }
    }
    return 0;
}
