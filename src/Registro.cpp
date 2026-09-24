// Registro.cpp
// Implementación de la clase Registro.

#include "Registro.h"
#include "Utilidades.h"

#include <iostream>
#include <iomanip>
#include <fstream>   // ifstream (leer archivos) y ofstream (escribir archivos)
#include <sstream>   // stringstream (separar una línea por comas)

using namespace std;

// Cada línea del CSV debe tener exactamente 12 campos en este orden
const int TOTAL_CAMPOS = 12;
const string NOMBRES_CAMPOS[TOTAL_CAMPOS] = {
    "nombre", "equipo", "posicion", "edad", "nacionalidad",
    "partidos_jugados", "partidos_titular", "minutos", "goles",
    "asistencias", "tarjetas_amarillas", "tarjetas_rojas"
};

// Índices (posiciones dentro de la línea) de los campos que deben ser números
const int TOTAL_NUMERICOS = 8;
const int CAMPOS_NUMERICOS[TOTAL_NUMERICOS] = {3, 5, 6, 7, 8, 9, 10, 11};

// Ancho total de la tabla (suma de los setw del encabezado)
const int ANCHO_TABLA = 122;

// Función auxiliar: revisa que la posición sea una de las 4 permitidas
bool esPosicionValida(const string& posicion) {
    string p = aMinusculas(posicion);
    return p == "portero" || p == "defensa" || p == "mediocampista" || p == "delantero";
}

int Registro::cargarDesdeCSV(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "  Error: no se pudo abrir el archivo \"" << ruta << "\"." << endl;
        cout << "  Revisa que la ruta sea correcta y que ejecutes el programa desde"
             << " la carpeta principal del proyecto." << endl;
        return 0;
    }

    // Los jugadores se guardan primero en un vector temporal. Solo si la carga
    // sale bien reemplazamos los datos anteriores; así, si el archivo está mal,
    // no perdemos lo que ya estaba cargado.
    vector<Jugador> nuevos;
    string linea;
    int numeroLinea = 0;
    int lineasIgnoradas = 0;
    bool esPrimeraLinea = true;

    while (getline(archivo, linea)) {
        numeroLinea++;
        linea = limpiarEspacios(linea);

        // Las líneas vacías simplemente se saltan
        if (linea.empty()) {
            continue;
        }

        // La primera línea con texto es la cabecera si empieza con "nombre"
        if (esPrimeraLinea) {
            esPrimeraLinea = false;
            if (aMinusculas(linea).substr(0, 6) == "nombre") {
                continue;
            }
        }

        // Separamos la línea por comas. stringstream nos permite usar getline
        // sobre un texto como si fuera un archivo, usando ',' como separador.
        vector<string> campos;
        stringstream separador(linea);
        string campo;
        while (getline(separador, campo, ',')) {
            campos.push_back(limpiarEspacios(campo));
        }

        // Validación 1: número correcto de campos
        int cantidadCampos = campos.size();
        if (cantidadCampos != TOTAL_CAMPOS) {
            cout << "  Linea " << numeroLinea << " ignorada: se esperaban "
                 << TOTAL_CAMPOS << " campos y tiene " << cantidadCampos << "." << endl;
            lineasIgnoradas++;
            continue;
        }

        // Validación 2: los campos de texto no pueden estar vacíos
        if (campos[0].empty() || campos[1].empty() || campos[2].empty() || campos[4].empty()) {
            cout << "  Linea " << numeroLinea << " ignorada: tiene campos de texto vacios." << endl;
            lineasIgnoradas++;
            continue;
        }

        // Validación 3: los campos numéricos deben ser enteros no negativos.
        // Guardamos cada número en 'valores' usando el mismo índice del campo.
        int valores[TOTAL_CAMPOS] = {0};
        bool numerosValidos = true;
        for (int i = 0; i < TOTAL_NUMERICOS && numerosValidos; i++) {
            int indice = CAMPOS_NUMERICOS[i];
            if (!convertirAEntero(campos[indice], valores[indice])) {
                cout << "  Linea " << numeroLinea << " ignorada: el campo '"
                     << NOMBRES_CAMPOS[indice] << "' no es un numero valido (\""
                     << campos[indice] << "\")." << endl;
                numerosValidos = false;
            }
        }
        if (!numerosValidos) {
            lineasIgnoradas++;
            continue;
        }

        // Validación 4: datos que no tienen sentido
        if (!esPosicionValida(campos[2])) {
            cout << "  Linea " << numeroLinea << " ignorada: posicion desconocida (\""
                 << campos[2] << "\")." << endl;
            lineasIgnoradas++;
            continue;
        }
        if (valores[3] < 15 || valores[3] > 50) {
            cout << "  Linea " << numeroLinea << " ignorada: edad fuera de rango (" << valores[3] << ")." << endl;
            lineasIgnoradas++;
            continue;
        }
        if (valores[6] > valores[5]) {
            cout << "  Linea " << numeroLinea << " ignorada: tiene mas partidos de titular"
                 << " que partidos jugados." << endl;
            lineasIgnoradas++;
            continue;
        }

        // Si pasó todas las validaciones, creamos el jugador
        Jugador jugador(campos[0], campos[1], campos[2], valores[3], campos[4],
                        valores[5], valores[6], valores[7], valores[8],
                        valores[9], valores[10], valores[11]);
        nuevos.push_back(jugador);
    }

    archivo.close();

    if (lineasIgnoradas > 0) {
        cout << "  Aviso: se ignoraron " << lineasIgnoradas << " lineas con errores." << endl;
    }

    if (nuevos.empty()) {
        cout << "  Error: el archivo no contiene jugadores validos." << endl;
        return 0;
    }

    jugadores = nuevos;
    return jugadores.size();
}

void Registro::mostrarTodos() const {
    mostrarLista(jugadores, 0);
}

void Registro::mostrarLista(const vector<Jugador>& lista, int limite) const {
    int n = lista.size();
    if (n == 0) {
        cout << "  (No hay jugadores para mostrar)" << endl;
        return;
    }
    if (limite <= 0 || limite > n) {
        limite = n;
    }

    // Encabezado: los anchos coinciden con los de Jugador::mostrar()
    cout << endl;
    cout << left
         << setw(5) << "#"
         << setw(24) << "Nombre"
         << setw(18) << "Equipo"
         << setw(14) << "Posicion"
         << right << setw(4) << "Edad" << "  "
         << left << setw(18) << "Nacionalidad"
         << right
         << setw(4) << "PJ"
         << setw(4) << "PT"
         << setw(6) << "Min"
         << setw(4) << "G"
         << setw(4) << "A"
         << setw(4) << "TA"
         << setw(4) << "TR"
         << setw(7) << "G/90"
         << endl;
    cout << string(ANCHO_TABLA, '-') << endl;

    for (int i = 0; i < limite; i++) {
        cout << left << setw(5) << i + 1;   // número de fila (empieza en 1)
        lista[i].mostrar();
    }

    cout << string(ANCHO_TABLA, '-') << endl;
    cout << "Mostrando " << limite << " de " << n << " jugadores." << endl;
    cout << "PJ=partidos jugados  PT=partidos titular  Min=minutos  G=goles  A=asistencias"
         << "  TA/TR=tarjetas amarillas/rojas  G/90=goles por 90 min" << endl;
}

const vector<Jugador>& Registro::getJugadores() const {
    return jugadores;
}

int Registro::getCantidad() const {
    return jugadores.size();
}

// ----------------------- Filtros por texto -----------------------
// Se comparan ambos textos en minúsculas para que "arsenal" y "Arsenal"
// se consideren iguales.

vector<Jugador> Registro::filtrarPorEquipo(const string& equipo) const {
    vector<Jugador> resultado;
    string buscado = aMinusculas(limpiarEspacios(equipo));
    int n = jugadores.size();
    for (int i = 0; i < n; i++) {
        if (aMinusculas(jugadores[i].getEquipo()) == buscado) {
            resultado.push_back(jugadores[i]);
        }
    }
    return resultado;
}

vector<Jugador> Registro::filtrarPorPosicion(const string& posicion) const {
    vector<Jugador> resultado;
    string buscada = aMinusculas(limpiarEspacios(posicion));
    int n = jugadores.size();
    for (int i = 0; i < n; i++) {
        if (aMinusculas(jugadores[i].getPosicion()) == buscada) {
            resultado.push_back(jugadores[i]);
        }
    }
    return resultado;
}

vector<Jugador> Registro::filtrarPorNacionalidad(const string& nacionalidad) const {
    vector<Jugador> resultado;
    string buscada = aMinusculas(limpiarEspacios(nacionalidad));
    int n = jugadores.size();
    for (int i = 0; i < n; i++) {
        if (aMinusculas(jugadores[i].getNacionalidad()) == buscada) {
            resultado.push_back(jugadores[i]);
        }
    }
    return resultado;
}

// ----------------------- Filtros por rango -----------------------

vector<Jugador> Registro::filtrarPorRangoGoles(int minimo, int maximo) const {
    vector<Jugador> resultado;
    int n = jugadores.size();
    for (int i = 0; i < n; i++) {
        int goles = jugadores[i].getGoles();
        if (goles >= minimo && goles <= maximo) {
            resultado.push_back(jugadores[i]);
        }
    }
    return resultado;
}

vector<Jugador> Registro::filtrarPorRangoAsistencias(int minimo, int maximo) const {
    vector<Jugador> resultado;
    int n = jugadores.size();
    for (int i = 0; i < n; i++) {
        int asistencias = jugadores[i].getAsistencias();
        if (asistencias >= minimo && asistencias <= maximo) {
            resultado.push_back(jugadores[i]);
        }
    }
    return resultado;
}

vector<Jugador> Registro::filtrarPorRangoEdad(int minimo, int maximo) const {
    vector<Jugador> resultado;
    int n = jugadores.size();
    for (int i = 0; i < n; i++) {
        int edad = jugadores[i].getEdad();
        if (edad >= minimo && edad <= maximo) {
            resultado.push_back(jugadores[i]);
        }
    }
    return resultado;
}

vector<Jugador> Registro::filtrarPorRangoMinutos(int minimo, int maximo) const {
    vector<Jugador> resultado;
    int n = jugadores.size();
    for (int i = 0; i < n; i++) {
        int minutos = jugadores[i].getMinutos();
        if (minutos >= minimo && minutos <= maximo) {
            resultado.push_back(jugadores[i]);
        }
    }
    return resultado;
}

// ----------------------- Exportar -----------------------

bool Registro::exportarACSV(const string& ruta, const vector<Jugador>& datos) const {
    ofstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    // Cabecera: los nombres de los campos separados por comas
    for (int i = 0; i < TOTAL_CAMPOS; i++) {
        archivo << NOMBRES_CAMPOS[i];
        if (i < TOTAL_CAMPOS - 1) {
            archivo << ",";
        }
    }
    archivo << "\n";

    int n = datos.size();
    for (int i = 0; i < n; i++) {
        const Jugador& j = datos[i];
        archivo << j.getNombre() << ","
                << j.getEquipo() << ","
                << j.getPosicion() << ","
                << j.getEdad() << ","
                << j.getNacionalidad() << ","
                << j.getPartidosJugados() << ","
                << j.getPartidosTitular() << ","
                << j.getMinutos() << ","
                << j.getGoles() << ","
                << j.getAsistencias() << ","
                << j.getTarjetasAmarillas() << ","
                << j.getTarjetasRojas() << "\n";
    }

    archivo.close();
    return true;
}
