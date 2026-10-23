#include "Registro.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

// ============================ Catálogos ============================

// O(k): lee un archivo de texto (k líneas) y guarda cada línea en 'destino'.
// Regresa false si el archivo no existe o está vacío.
bool Registro::leerCatalogo(string ruta, vector<string>& destino) {
    destino.clear();
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error: no se encontro el archivo " << ruta << endl;
        return false;
    }
    string linea;
    while (getline(archivo, linea)) {
        // Los archivos de Windows terminan cada línea con '\r'; se quita
        if (linea.size() > 0 && linea[linea.size() - 1] == '\r') {
            linea.erase(linea.size() - 1);
        }
        if (linea.size() > 0) {
            destino.push_back(linea);
        }
    }
    archivo.close();
    if (destino.size() == 0) {
        cout << "Error: el archivo " << ruta << " esta vacio" << endl;
        return false;
    }
    return true;
}

// O(e + p)
bool Registro::cargarCatalogos(string rutaEquipos, string rutaPosiciones) {
    bool equiposBien = leerCatalogo(rutaEquipos, equipos);
    bool posicionesBien = leerCatalogo(rutaPosiciones, posiciones);
    return equiposBien && posicionesBien;
}

// O(k): búsqueda secuencial en el catálogo
bool Registro::estaEnCatalogo(string valor, const vector<string>& catalogo) const {
    for (int i = 0; i < (int)catalogo.size(); i++) {
        if (catalogo[i] == valor) {
            return true;
        }
    }
    return false;
}

vector<string> Registro::getEquipos() const {
    return equipos;
}

vector<string> Registro::getPosiciones() const {
    return posiciones;
}

// ============================ Carga del CSV ============================

// Regresa true si el texto solo tiene dígitos. Se revisa antes de usar stoi,
// porque stoi falla si el texto es, por ejemplo, "abc".
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

// O(n·(h + e + p)): por cada línea se revisan los catálogos, se inserta en el
// árbol en O(h) y al final de la lista en O(1)
int Registro::cargarDesdeCSV(string ruta) {
    if (equipos.size() == 0 || posiciones.size() == 0) {
        cout << "Error: no se puede validar el CSV porque faltan los catalogos" << endl
             << "(data/equipos.txt o data/posiciones.txt). Revisa esos archivos." << endl;
        return 0;
    }

    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir el archivo " << ruta << endl;
        return 0;
    }

    lista.vaciar();   // para no duplicar jugadores si se carga dos veces
    arbol.vaciar();

    string linea;
    getline(archivo, linea);   // se salta la cabecera

    int numeroLinea = 1;
    int descartadas = 0;
    while (getline(archivo, linea)) {
        numeroLinea++;
        if (linea.size() > 0 && linea[linea.size() - 1] == '\r') {
            linea.erase(linea.size() - 1);
        }
        if (linea.size() == 0) {
            continue;
        }

        vector<string> campos;
        stringstream separador(linea);
        string campo;
        while (getline(separador, campo, ',')) {
            campos.push_back(campo);
        }

        // Si algo está mal, 'motivo' explica por qué se descarta la línea
        string motivo = "";
        if (campos.size() != 12) {
            motivo = "le faltan campos";
        } else {
            // Todos son números, menos nombre[0], equipo[1], posicion[2] y nacionalidad[4]
            for (int i = 3; i < 12; i++) {
                if (i != 4 && !esNumero(campos[i])) {
                    motivo = "tiene un numero invalido";
                }
            }
            if (motivo == "" && !estaEnCatalogo(campos[1], equipos)) {
                motivo = "equipo desconocido (" + campos[1] + ")";
            }
            if (motivo == "" && !estaEnCatalogo(campos[2], posiciones)) {
                motivo = "posicion desconocida (" + campos[2] + ")";
            }
        }

        if (motivo == "") {
            Jugador jugador(campos[0], campos[1], campos[2], stoi(campos[3]),
                            campos[4], stoi(campos[5]), stoi(campos[6]),
                            stoi(campos[7]), stoi(campos[8]), stoi(campos[9]),
                            stoi(campos[10]), stoi(campos[11]));
            // Se inserta primero en el árbol porque él detecta los nombres
            // repetidos; solo si entró al árbol se agrega a la lista
            if (arbol.insertar(jugador)) {
                lista.insertarAlFinal(jugador);
            } else {
                motivo = "nombre repetido (" + campos[0] + ")";
            }
        }

        if (motivo != "") {
            cout << "Linea " << numeroLinea << " descartada: " << motivo << endl;
            descartadas++;
        }
    }
    archivo.close();

    cout << "Lineas cargadas: " << lista.obtenerTamano()
         << " | Lineas descartadas: " << descartadas << endl;
    return lista.obtenerTamano();
}

// ============================ Mostrar ============================

void Registro::mostrarEncabezado() const {
    cout << endl;
    cout << left << setw(24) << "Nombre"
         << setw(18) << "Equipo"
         << setw(14) << "Posicion"
         << right << setw(4) << "Edad" << "  "
         << left << setw(18) << "Nacionalidad"
         << right << setw(4) << "PJ" << setw(4) << "PT" << setw(6) << "Min"
         << setw(4) << "G" << setw(4) << "A" << setw(4) << "TA" << setw(4) << "TR"
         << setw(7) << "G/90" << endl;
    cout << string(117, '-') << endl;
}

void Registro::mostrarPie(int mostrados) const {
    cout << string(117, '-') << endl;
    cout << "Jugadores mostrados: " << mostrados << endl;
    cout << "PJ=partidos jugados  PT=partidos titular  Min=minutos  G=goles  A=asistencias"
         << "  TA/TR=tarjetas amarillas/rojas  G/90=goles por 90 min" << endl;
}

// O(n): lista de la cabeza a la cola
void Registro::mostrarOrdenDeCarga() const {
    mostrarEncabezado();
    lista.mostrarAdelante();
    mostrarPie(lista.obtenerTamano());
}

// O(n): lista de la cola a la cabeza
void Registro::mostrarOrdenInverso() const {
    mostrarEncabezado();
    lista.mostrarAtras();
    mostrarPie(lista.obtenerTamano());
}

// O(n): recorrido inorden del árbol
void Registro::mostrarAlfabetico() const {
    mostrarEncabezado();
    arbol.inorden();
    mostrarPie(lista.obtenerTamano());
}

void Registro::mostrarLista(const vector<Jugador>& jugadores, int cantidad) const {
    int n = jugadores.size();
    if (cantidad <= 0 || cantidad > n) {
        cantidad = n;
    }
    mostrarEncabezado();
    for (int i = 0; i < cantidad; i++) {
        cout << jugadores[i] << endl;
    }
    mostrarPie(cantidad);
}

// O(n): copia de la lista
vector<Jugador> Registro::getJugadores() const {
    return lista.aVector();
}

int Registro::getCantidad() const {
    return lista.obtenerTamano();
}

// ============================ Consultas ============================

// O(n): búsqueda secuencial en la lista
bool Registro::buscarEnLista(string nombre, Jugador& encontrado, int& pasos) const {
    // Jugador temporal que solo tiene el nombre: como los operadores de
    // Jugador comparan solo el nombre, es todo lo que se necesita para buscar
    Jugador buscado(nombre);
    Jugador* resultado = lista.buscar(buscado, pasos);
    if (resultado == nullptr) {
        return false;
    }
    encontrado = *resultado;   // "*resultado" es el jugador al que apunta
    return true;
}

// O(h): búsqueda en el árbol
bool Registro::buscarEnArbol(string nombre, Jugador& encontrado, int& pasos) const {
    Jugador buscado(nombre);   // jugador temporal, igual que arriba
    Jugador* resultado = arbol.buscar(buscado, pasos);
    if (resultado == nullptr) {
        return false;
    }
    encontrado = *resultado;
    return true;
}

// O(n)
int Registro::alturaArbol() const {
    return arbol.altura();
}

// O(n) los tres primeros; O(n·h) por niveles
void Registro::mostrarRecorrido(int tipo) const {
    mostrarEncabezado();
    if (tipo == 1) {
        arbol.preorden();
    } else if (tipo == 2) {
        arbol.inorden();
    } else if (tipo == 3) {
        arbol.postorden();
    } else {
        arbol.porNiveles();
    }
    mostrarPie(lista.obtenerTamano());
}

// O(h)
int Registro::nivelDe(string nombre) const {
    return arbol.nivelDe(Jugador(nombre));
}

// O(h)
vector<Jugador> Registro::ancestrosDe(string nombre) const {
    return arbol.ancestros(Jugador(nombre));
}

// ============================ Filtros ============================

// O(n) cada uno: copian la lista a un vector y lo recorren

vector<Jugador> Registro::filtrarPorEquipo(string equipo) const {
    vector<Jugador> todos = lista.aVector();
    vector<Jugador> resultado;
    for (int i = 0; i < (int)todos.size(); i++) {
        if (todos[i].getEquipo() == equipo) {
            resultado.push_back(todos[i]);
        }
    }
    return resultado;
}

vector<Jugador> Registro::filtrarPorPosicion(string posicion) const {
    vector<Jugador> todos = lista.aVector();
    vector<Jugador> resultado;
    for (int i = 0; i < (int)todos.size(); i++) {
        if (todos[i].getPosicion() == posicion) {
            resultado.push_back(todos[i]);
        }
    }
    return resultado;
}

vector<Jugador> Registro::filtrarPorRangoGoles(int minimo, int maximo) const {
    vector<Jugador> todos = lista.aVector();
    vector<Jugador> resultado;
    for (int i = 0; i < (int)todos.size(); i++) {
        int goles = todos[i].getGoles();
        if (goles >= minimo && goles <= maximo) {
            resultado.push_back(todos[i]);
        }
    }
    return resultado;
}
