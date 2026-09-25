// Registro.cpp
// Implementación de la clase Registro.

#include "Registro.h"

#include <iostream>
#include <iomanip>
#include <fstream>   // ifstream para leer archivos
#include <sstream>   // stringstream para separar una línea por comas

// Función auxiliar: regresa true si el texto solo tiene dígitos (ej. "305").
// Se revisa antes de usar stoi, porque stoi falla si el texto es "abc".
bool esNumero(string texto) {
    if (texto.size() == 0) {
        return false;
    }
    for (int i = 0; i < (int)texto.size(); i++) {
        if (texto[i] < '0' || texto[i] > '9') {
            return false;
        }
    }
    return true;
}

int Registro::cargarDesdeCSV(string ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir el archivo " << ruta << endl;
        return 0;
    }

    jugadores.clear();   // si se carga dos veces, no se duplican los jugadores

    string linea;
    getline(archivo, linea);   // la primera línea es la cabecera, se salta

    int numeroLinea = 1;
    while (getline(archivo, linea)) {
        numeroLinea++;

        // Los archivos creados en Windows terminan cada línea con '\r';
        // si está, lo quitamos para que no se pegue al último número.
        if (linea.size() > 0 && linea[linea.size() - 1] == '\r') {
            linea.erase(linea.size() - 1);
        }
        if (linea.size() == 0) {
            continue;   // línea vacía
        }

        // Separamos la línea por comas
        vector<string> campos;
        stringstream separador(linea);
        string campo;
        while (getline(separador, campo, ',')) {
            campos.push_back(campo);
        }

        // Validación 1: deben ser exactamente 12 campos
        if (campos.size() != 12) {
            cout << "Linea " << numeroLinea << " ignorada: le faltan campos." << endl;
            continue;
        }

        // Validación 2: los campos numéricos deben ser números
        // (todos menos nombre[0], equipo[1], posicion[2] y nacionalidad[4])
        bool datosValidos = true;
        for (int i = 3; i < 12; i++) {
            if (i != 4 && !esNumero(campos[i])) {
                datosValidos = false;
            }
        }
        if (!datosValidos) {
            cout << "Linea " << numeroLinea << " ignorada: tiene un numero invalido." << endl;
            continue;
        }

        // stoi convierte un texto a entero, por ejemplo "25" -> 25
        Jugador jugador(campos[0], campos[1], campos[2], stoi(campos[3]),
                        campos[4], stoi(campos[5]), stoi(campos[6]),
                        stoi(campos[7]), stoi(campos[8]), stoi(campos[9]),
                        stoi(campos[10]), stoi(campos[11]));
        jugadores.push_back(jugador);
    }

    archivo.close();
    return jugadores.size();
}

void Registro::mostrarTodos() const {
    mostrarLista(jugadores, 0);
}

void Registro::mostrarLista(const vector<Jugador>& lista, int cantidad) const {
    int n = lista.size();
    if (cantidad <= 0 || cantidad > n) {
        cantidad = n;
    }

    // Encabezado de la tabla: los anchos coinciden con Jugador::mostrar()
    cout << endl;
    cout << left << setw(5) << "#"
         << setw(24) << "Nombre"
         << setw(18) << "Equipo"
         << setw(14) << "Posicion"
         << right << setw(4) << "Edad" << "  "
         << left << setw(18) << "Nacionalidad"
         << right << setw(4) << "PJ" << setw(4) << "PT" << setw(6) << "Min"
         << setw(4) << "G" << setw(4) << "A" << setw(4) << "TA" << setw(4) << "TR"
         << setw(7) << "G/90" << endl;
    cout << string(122, '-') << endl;

    for (int i = 0; i < cantidad; i++) {
        cout << left << setw(5) << i + 1;   // número de fila
        lista[i].mostrar();
    }

    cout << string(122, '-') << endl;
    cout << "Mostrando " << cantidad << " de " << n << " jugadores." << endl;
    cout << "PJ=partidos jugados  PT=partidos titular  Min=minutos  G=goles  A=asistencias"
         << "  TA/TR=tarjetas amarillas/rojas  G/90=goles por 90 min" << endl;
}

vector<Jugador> Registro::getJugadores() const {
    return jugadores;
}

int Registro::getCantidad() const {
    return jugadores.size();
}

vector<Jugador> Registro::filtrarPorEquipo(string equipo) const {
    vector<Jugador> resultado;
    for (int i = 0; i < (int)jugadores.size(); i++) {
        if (jugadores[i].getEquipo() == equipo) {
            resultado.push_back(jugadores[i]);
        }
    }
    return resultado;
}

vector<Jugador> Registro::filtrarPorPosicion(string posicion) const {
    vector<Jugador> resultado;
    for (int i = 0; i < (int)jugadores.size(); i++) {
        if (jugadores[i].getPosicion() == posicion) {
            resultado.push_back(jugadores[i]);
        }
    }
    return resultado;
}

vector<Jugador> Registro::filtrarPorRangoGoles(int minimo, int maximo) const {
    vector<Jugador> resultado;
    for (int i = 0; i < (int)jugadores.size(); i++) {
        int goles = jugadores[i].getGoles();
        if (goles >= minimo && goles <= maximo) {
            resultado.push_back(jugadores[i]);
        }
    }
    return resultado;
}
