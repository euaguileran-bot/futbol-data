#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Jugador.h"
#include "Registro.h"
#include "Ordenamientos.h"

const string RUTA_CSV = "data/jugadores.csv";
const string RUTA_EQUIPOS = "data/equipos.txt";
const string RUTA_POSICIONES = "data/posiciones.txt";

// Si el usuario escribe una letra, cin.clear() quita el error y cin.ignore()
// descarta lo escrito, así se vuelve a preguntar sin que el programa se rompa
int leerEntero(int minimo, int maximo) {
    int numero;
    cin >> numero;
    while (cin.fail() || numero < minimo || numero > maximo) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Entrada invalida. Escribe un numero entre " << minimo
             << " y " << maximo << ": ";
        cin >> numero;
    }
    return numero;
}

// Lee un archivo de texto y regresa cada línea como un elemento del vector
vector<string> leerLista(string ruta) {
    vector<string> lista;
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir el archivo " << ruta << endl;
        return lista;
    }
    string linea;
    while (getline(archivo, linea)) {
        // Los archivos de Windows terminan cada línea con '\r'; se quita
        if (linea.size() > 0 && linea[linea.size() - 1] == '\r') {
            linea.erase(linea.size() - 1);
        }
        if (linea.size() > 0) {
            lista.push_back(linea);
        }
    }
    return lista;
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

void mostrarMenu() {
    cout << endl;
    cout << "==== ANALIZADOR PREMIER LEAGUE ====" << endl;
    cout << "1. Cargar jugadores desde CSV" << endl;
    cout << "2. Mostrar todos los jugadores" << endl;
    cout << "3. Ordenar jugadores" << endl;
    cout << "4. Filtrar jugadores" << endl;
    cout << "0. Salir" << endl;
    cout << "Elige una opcion (0-4): ";
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

    // Se ordena una copia para no alterar el orden original del CSV
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

    if (tipo == 1) {
        vector<string> equipos = leerLista(RUTA_EQUIPOS);
        if (equipos.size() == 0) {
            return;
        }
        resultado = registro.filtrarPorEquipo(elegirDeLista(equipos));
    } else if (tipo == 2) {
        vector<string> posiciones = leerLista(RUTA_POSICIONES);
        if (posiciones.size() == 0) {
            return;
        }
        resultado = registro.filtrarPorPosicion(elegirDeLista(posiciones));
    } else {
        cout << "Goles minimos: ";
        int minimo = leerEntero(0, 100);
        cout << "Goles maximos: ";
        int maximo = leerEntero(minimo, 100);
        resultado = registro.filtrarPorRangoGoles(minimo, maximo);
    }

    if (resultado.size() == 0) {
        cout << "No se encontraron jugadores con ese filtro." << endl;
    } else {
        registro.mostrarLista(resultado, 0);
    }
}

int main() {
    Registro registro;
    int opcion = -1;

    while (opcion != 0) {
        mostrarMenu();
        opcion = leerEntero(0, 4);

        if (opcion >= 2 && registro.getCantidad() == 0) {
            cout << "Primero carga los jugadores con la opcion 1." << endl;
            continue;
        }

        switch (opcion) {
            case 1: {
                int cantidad = registro.cargarDesdeCSV(RUTA_CSV);
                if (cantidad > 0) {
                    cout << ">> Se cargaron " << cantidad << " jugadores desde " << RUTA_CSV << endl;
                }
                break;
            }
            case 2:
                registro.mostrarTodos();
                break;
            case 3:
                opcionOrdenar(registro);
                break;
            case 4:
                opcionFiltrar(registro);
                break;
            case 0:
                cout << "Hasta luego!" << endl;
                break;
        }
    }
    return 0;
}
