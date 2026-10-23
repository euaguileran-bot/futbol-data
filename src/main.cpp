#include <iostream>
#include <string>
#include <vector>
#include "Jugador.h"
#include "Registro.h"
#include "Ordenamientos.h"

const string RUTA_CSV = "data/jugadores.csv";
const string RUTA_EQUIPOS = "data/equipos.txt";
const string RUTA_POSICIONES = "data/posiciones.txt";

// Límites para validar lo que escribe el usuario
const int EDAD_MINIMA = 15;
const int EDAD_MAXIMA = 50;
const int PARTIDOS_POR_TEMPORADA = 38;
const int MAXIMO_GOLES_ASISTENCIAS = 100;

// ============================ Lectura de datos ============================

// Si el usuario escribe una letra, cin.clear() quita el error y cin.ignore()
// descarta lo escrito, así se vuelve a preguntar sin que el programa se rompa
int leerEntero(int minimo, int maximo) {
    int numero;
    cin >> numero;
    while (cin.fail() || numero < minimo || numero > maximo) {
        // Si se acabó la entrada (Ctrl+Z en Windows, Ctrl+D en Linux) ya no se
        // puede leer nada: se regresa el mínimo para no quedarse en un ciclo
        // infinito. En el menú el mínimo es 0 (Salir), así que el programa termina.
        if (cin.eof()) {
            return minimo;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Entrada invalida. Escribe un numero entre " << minimo
             << " y " << maximo << ": ";
        cin >> numero;
    }
    cin.ignore(1000, '\n');   // quita el Enter para que después funcione getline
    return numero;
}

// Lee una línea completa (para nombres con espacios, por ejemplo "Declan Rice")
string leerTexto() {
    string texto;
    getline(cin, texto);
    while (texto.size() == 0 && !cin.eof()) {
        cout << "No puede quedar vacio. Escribe de nuevo: ";
        getline(cin, texto);
    }
    return texto;
}

int pedirDato(string texto, int minimo, int maximo) {
    cout << texto << " (" << minimo << "-" << maximo << "): ";
    return leerEntero(minimo, maximo);
}

// Muestra una lista numerada y regresa el elemento que elija el usuario
string elegirDeLista(const vector<string>& lista) {
    for (int i = 0; i < (int)lista.size(); i++) {
        cout << "  " << i + 1 << ". " << lista[i] << endl;
    }
    cout << "Elige una opcion (1-" << lista.size() << "): ";
    int opcion = leerEntero(1, lista.size());
    return lista[opcion - 1];
}

// Pide las 7 estadísticas y las guarda en el jugador con sus setters.
// Se usa al agregar y al actualizar.
void pedirEstadisticas(Jugador& jugador) {
    jugador.setPartidosJugados(pedirDato("Partidos jugados", 0, PARTIDOS_POR_TEMPORADA));
    int jugados = jugador.getPartidosJugados();
    jugador.setPartidosTitular(pedirDato("Partidos de titular", 0, jugados));
    jugador.setMinutos(pedirDato("Minutos", 0, jugados * 90));
    jugador.setGoles(pedirDato("Goles", 0, MAXIMO_GOLES_ASISTENCIAS));
    jugador.setAsistencias(pedirDato("Asistencias", 0, MAXIMO_GOLES_ASISTENCIAS));
    jugador.setTarjetasAmarillas(pedirDato("Tarjetas amarillas", 0, jugados));
    jugador.setTarjetasRojas(pedirDato("Tarjetas rojas", 0, jugados));
}

// ============================ Opciones del menú ============================

void mostrarMenu() {
    cout << endl;
    cout << "==== ANALIZADOR PREMIER LEAGUE ====" << endl;
    cout << "1. Cargar jugadores desde CSV" << endl;
    cout << "2. Mostrar jugadores" << endl;
    cout << "3. Ordenar jugadores" << endl;
    cout << "4. Filtrar jugadores" << endl;
    cout << "5. Buscar jugador por nombre" << endl;
    cout << "6. Agregar jugador" << endl;
    cout << "7. Actualizar estadisticas de un jugador" << endl;
    cout << "8. Eliminar jugador" << endl;
    cout << "9. Informacion del arbol" << endl;
    cout << "0. Salir" << endl;
    cout << "Elige una opcion (0-9): ";
}

void opcionMostrar(const Registro& registro) {
    cout << endl << "--- MOSTRAR JUGADORES ---" << endl;
    cout << "1 = orden de carga (lista hacia adelante)" << endl;
    cout << "2 = orden inverso (lista hacia atras)" << endl;
    cout << "3 = alfabetico (recorrido inorden del arbol)" << endl;
    cout << "Elige (1-3): ";
    int tipo = leerEntero(1, 3);
    if (tipo == 1) {
        registro.mostrarOrdenDeCarga();
    } else if (tipo == 2) {
        registro.mostrarOrdenInverso();
    } else {
        registro.mostrarAlfabetico();
    }
}

void opcionOrdenar(const Registro& registro) {
    cout << endl << "--- ORDENAR JUGADORES ---" << endl;
    cout << "Criterio: 1 = goles, 2 = asistencias, 3 = edad, 4 = minutos, 5 = nombre" << endl;
    cout << "Elige el criterio (1-5): ";
    int criterio = leerEntero(1, 5);

    cout << "Orden: 1 = ascendente (menor a mayor / A-Z), 2 = descendente (mayor a menor / Z-A)" << endl;
    cout << "Elige el orden (1-2): ";
    bool ascendente = (leerEntero(1, 2) == 1);

    cout << "Algoritmo: 1 = Bubble Sort, 2 = Merge Sort" << endl;
    cout << "Elige el algoritmo (1-2): ";
    int algoritmo = leerEntero(1, 2);

    // Se ordena una copia de la lista (en un vector) para no alterar la lista
    vector<Jugador> copia = registro.getJugadores();
    string nombreAlgoritmo;
    if (algoritmo == 1) {
        bubbleSort(copia, criterio, ascendente);
        nombreAlgoritmo = "Bubble Sort";
    } else {
        mergeSort(copia, criterio, ascendente);
        nombreAlgoritmo = "Merge Sort";
    }

    cout << endl << ">> Algoritmo usado: " << nombreAlgoritmo
         << " | Jugadores procesados: " << copia.size()
         << " | Criterio: " << nombreCriterio(criterio);
    if (ascendente) {
        cout << " (ascendente)" << endl;
    } else {
        cout << " (descendente)" << endl;
    }
    cout << ">> Comparaciones realizadas: " << getComparaciones() << endl;

    cout << "Cuantos jugadores quieres ver? (0 = todos): ";
    int cantidad = leerEntero(0, copia.size());
    registro.mostrarLista(copia, cantidad);
}

void opcionFiltrar(const Registro& registro) {
    cout << endl << "--- FILTRAR JUGADORES ---" << endl;
    cout << "1. Por equipo" << endl;
    cout << "2. Por posicion" << endl;
    cout << "3. Por rango de goles" << endl;
    cout << "Elige el filtro (1-3): ";
    int tipo = leerEntero(1, 3);

    vector<Jugador> resultado;

    if (tipo == 1 || tipo == 2) {
        vector<string> opciones;
        if (tipo == 1) {
            opciones = registro.getEquipos();
        } else {
            opciones = registro.getPosiciones();
        }
        if (opciones.size() == 0) {
            cout << "No hay catalogo para este filtro. Revisa data/equipos.txt y data/posiciones.txt" << endl;
            return;
        }
        string elegido = elegirDeLista(opciones);
        if (tipo == 1) {
            resultado = registro.filtrarPorEquipo(elegido);
        } else {
            resultado = registro.filtrarPorPosicion(elegido);
        }
    } else {
        int minimo = pedirDato("Goles minimos", 0, MAXIMO_GOLES_ASISTENCIAS);
        int maximo = pedirDato("Goles maximos", minimo, MAXIMO_GOLES_ASISTENCIAS);
        resultado = registro.filtrarPorRangoGoles(minimo, maximo);
    }

    if (resultado.size() == 0) {
        cout << "No se encontraron jugadores con ese filtro." << endl;
    } else {
        registro.mostrarLista(resultado, 0);
    }
}

void opcionBuscar(const Registro& registro) {
    cout << endl << "--- BUSCAR JUGADOR ---" << endl;
    cout << "Nombre completo sin acentos (ej. Declan Rice): ";
    string nombre = leerTexto();
    cout << "Buscar en: 1 = lista (secuencial), 2 = arbol (BST), 3 = los dos para comparar" << endl;
    cout << "Elige (1-3): ";
    int donde = leerEntero(1, 3);

    Jugador encontrado;
    int pasos;
    bool loEncontro = false;

    if (donde == 1 || donde == 3) {
        int posicion = registro.buscarEnLista(nombre, encontrado, pasos);
        if (posicion == -1) {
            cout << ">> Lista: no se encontro (" << pasos << " pasos)" << endl;
        } else {
            cout << ">> Lista: encontrado en la posicion " << posicion
                 << " (" << pasos << " pasos)" << endl;
            loEncontro = true;
        }
    }
    if (donde == 2 || donde == 3) {
        if (registro.buscarEnArbol(nombre, encontrado, pasos)) {
            cout << ">> Arbol: encontrado (" << pasos << " pasos)" << endl;
            loEncontro = true;
        } else {
            cout << ">> Arbol: no se encontro (" << pasos << " pasos)" << endl;
        }
    }

    if (loEncontro) {
        vector<Jugador> uno;
        uno.push_back(encontrado);
        registro.mostrarLista(uno, 0);
    }
}

void opcionAgregar(Registro& registro) {
    cout << endl << "--- AGREGAR JUGADOR ---" << endl;
    vector<string> equipos = registro.getEquipos();
    vector<string> posiciones = registro.getPosiciones();
    if (equipos.size() == 0 || posiciones.size() == 0) {
        cout << "No se puede agregar: faltan los catalogos (data/equipos.txt o data/posiciones.txt)." << endl;
        return;
    }

    cout << "Nombre completo sin acentos: ";
    string nombre = leerTexto();
    if (registro.existeJugador(nombre)) {
        cout << "Ya existe un jugador con ese nombre." << endl;
        return;
    }
    cout << "Equipo:" << endl;
    string equipo = elegirDeLista(equipos);
    cout << "Posicion:" << endl;
    string posicion = elegirDeLista(posiciones);
    int edad = pedirDato("Edad", EDAD_MINIMA, EDAD_MAXIMA);
    cout << "Nacionalidad sin acentos: ";
    string nacionalidad = leerTexto();

    Jugador nuevo(nombre, equipo, posicion, edad, nacionalidad, 0, 0, 0, 0, 0, 0, 0);
    pedirEstadisticas(nuevo);

    cout << "Agregar en la lista: 1 = al final, 2 = al inicio" << endl;
    cout << "Elige (1-2): ";
    bool alInicio = (leerEntero(1, 2) == 2);

    registro.agregarJugador(nuevo, alInicio);
    cout << ">> Jugador agregado. Lista: " << registro.getCantidad()
         << " jugadores | Arbol: " << registro.getCantidadEnArbol() << " nodos" << endl;
}

void opcionActualizar(Registro& registro) {
    cout << endl << "--- ACTUALIZAR ESTADISTICAS ---" << endl;
    cout << "Nombre del jugador: ";
    string nombre = leerTexto();
    Jugador jugador;
    int pasos;
    if (!registro.buscarEnArbol(nombre, jugador, pasos)) {
        cout << "No se encontro a " << nombre << endl;
        return;
    }

    vector<Jugador> antes;
    antes.push_back(jugador);
    cout << "Datos actuales:";
    registro.mostrarLista(antes, 0);

    cout << "Escribe los nuevos valores:" << endl;
    pedirEstadisticas(jugador);
    registro.actualizarJugador(jugador);

    vector<Jugador> despues;
    despues.push_back(jugador);
    cout << ">> Jugador actualizado en la lista y en el arbol:";
    registro.mostrarLista(despues, 0);
}

void opcionEliminar(Registro& registro) {
    cout << endl << "--- ELIMINAR JUGADOR ---" << endl;
    cout << "Nombre del jugador: ";
    string nombre = leerTexto();
    Jugador jugador;
    int pasos;
    if (!registro.buscarEnArbol(nombre, jugador, pasos)) {
        cout << "No se encontro a " << nombre << endl;
        return;
    }

    vector<Jugador> uno;
    uno.push_back(jugador);
    registro.mostrarLista(uno, 0);
    cout << "Seguro que quieres eliminarlo? 1 = si, 2 = no: ";
    if (leerEntero(1, 2) == 2) {
        cout << "No se elimino." << endl;
        return;
    }

    registro.eliminarJugador(jugador.getNombre());
    cout << ">> Jugador eliminado. Lista: " << registro.getCantidad()
         << " jugadores | Arbol reconstruido: " << registro.getCantidadEnArbol() << " nodos" << endl;
}

void opcionArbol(const Registro& registro) {
    cout << endl << "--- INFORMACION DEL ARBOL ---" << endl;
    cout << "Jugadores en la lista: " << registro.getCantidad()
         << " | Nodos en el arbol: " << registro.getCantidadEnArbol() << endl;
    cout << "Altura del arbol: " << registro.alturaArbol() << " niveles (la raiz es el nivel 1)" << endl;
    cout << "1. Recorrido preorden" << endl;
    cout << "2. Recorrido inorden" << endl;
    cout << "3. Recorrido postorden" << endl;
    cout << "4. Recorrido por niveles" << endl;
    cout << "5. Nivel y ancestros de un jugador" << endl;
    cout << "0. Volver" << endl;
    cout << "Elige (0-5): ";
    int opcion = leerEntero(0, 5);

    if (opcion >= 1 && opcion <= 4) {
        registro.mostrarRecorrido(opcion);
    } else if (opcion == 5) {
        cout << "Nombre del jugador: ";
        string nombre = leerTexto();
        int nivel = registro.nivelDe(nombre);
        if (nivel == -1) {
            cout << "No se encontro a " << nombre << endl;
            return;
        }
        cout << ">> Esta en el nivel " << nivel << " del arbol" << endl;
        vector<Jugador> ancestros = registro.ancestrosDe(nombre);
        if (ancestros.size() == 0) {
            cout << ">> Es la raiz, no tiene ancestros." << endl;
        } else {
            cout << ">> Ancestros (de la raiz hasta su padre):";
            registro.mostrarLista(ancestros, 0);
        }
    }
}

// ================================== main ==================================

int main() {
    Registro registro;

    // Los catálogos se leen antes del menú. Si falta alguno, el programa sigue
    // funcionando, pero no podrá cargar el CSV ni agregar jugadores.
    if (registro.cargarCatalogos(RUTA_EQUIPOS, RUTA_POSICIONES)) {
        cout << ">> Catalogos cargados: " << registro.getEquipos().size() << " equipos y "
             << registro.getPosiciones().size() << " posiciones" << endl;
    } else {
        cout << "Aviso: sin los catalogos no se podra cargar el CSV ni agregar jugadores." << endl;
    }

    int opcion = -1;
    while (opcion != 0) {
        mostrarMenu();
        opcion = leerEntero(0, 9);

        // Todas menos cargar (1), agregar (6) y salir (0) necesitan jugadores
        bool necesitaJugadores = (opcion != 0 && opcion != 1 && opcion != 6);
        if (necesitaJugadores && registro.getCantidad() == 0) {
            cout << "No hay jugadores. Carga el CSV con la opcion 1 o agrega uno con la opcion 6." << endl;
            continue;
        }

        switch (opcion) {
            case 1: {
                int cantidad = registro.cargarDesdeCSV(RUTA_CSV);
                if (cantidad > 0) {
                    cout << ">> Se cargaron " << cantidad << " jugadores en la lista y "
                         << registro.getCantidadEnArbol() << " en el arbol" << endl;
                }
                break;
            }
            case 2: opcionMostrar(registro); break;
            case 3: opcionOrdenar(registro); break;
            case 4: opcionFiltrar(registro); break;
            case 5: opcionBuscar(registro); break;
            case 6: opcionAgregar(registro); break;
            case 7: opcionActualizar(registro); break;
            case 8: opcionEliminar(registro); break;
            case 9: opcionArbol(registro); break;
            case 0: cout << "Hasta luego!" << endl; break;
        }
    }
    return 0;
}
