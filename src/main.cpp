#include <iostream>
#include <string>
#include <vector>
#include "Jugador.h"
#include "Registro.h"
#include "Ordenamientos.h"

const string RUTA_CSV = "data/jugadores.csv";

const int TOTAL_EQUIPOS = 20;
const string EQUIPOS[TOTAL_EQUIPOS] = {
    "Arsenal", "Aston Villa", "Bournemouth", "Brentford", "Brighton",
    "Burnley", "Chelsea", "Crystal Palace", "Everton", "Fulham",
    "Leeds United", "Liverpool", "Manchester City", "Manchester United", "Newcastle",
    "Nottingham Forest", "Sunderland", "Tottenham", "West Ham", "Wolves"
};

const int TOTAL_POSICIONES = 4;
const string POSICIONES[TOTAL_POSICIONES] = {"Portero", "Defensa", "Mediocampista", "Delantero"};

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
        for (int i = 0; i < TOTAL_EQUIPOS; i++) {
            cout << "  " << i + 1 << ". " << EQUIPOS[i] << endl;
        }
        cout << "Elige el equipo (1-" << TOTAL_EQUIPOS << "): ";
        int equipo = leerEntero(1, TOTAL_EQUIPOS);
        resultado = registro.filtrarPorEquipo(EQUIPOS[equipo - 1]);
    } else if (tipo == 2) {
        for (int i = 0; i < TOTAL_POSICIONES; i++) {
            cout << "  " << i + 1 << ". " << POSICIONES[i] << endl;
        }
        cout << "Elige la posicion (1-" << TOTAL_POSICIONES << "): ";
        int posicion = leerEntero(1, TOTAL_POSICIONES);
        resultado = registro.filtrarPorPosicion(POSICIONES[posicion - 1]);
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
