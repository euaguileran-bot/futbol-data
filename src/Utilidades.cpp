// Utilidades.cpp
// Implementación de las funciones auxiliares de texto.

#include "Utilidades.h"

using namespace std;

string aMinusculas(const string& texto) {
    string resultado = texto;
    int n = resultado.size();
    for (int i = 0; i < n; i++) {
        // En la tabla ASCII las mayúsculas y minúsculas están a la misma
        // distancia, así que basta con "recorrer" la letra.
        if (resultado[i] >= 'A' && resultado[i] <= 'Z') {
            resultado[i] = resultado[i] - 'A' + 'a';
        }
    }
    return resultado;
}

// Función auxiliar: indica si un carácter es un "espacio en blanco".
bool esEspacio(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

string limpiarEspacios(const string& texto) {
    int inicio = 0;
    int fin = texto.size();
    fin = fin - 1;

    // Avanzamos 'inicio' mientras haya espacios al principio
    while (inicio <= fin && esEspacio(texto[inicio])) {
        inicio++;
    }
    // Retrocedemos 'fin' mientras haya espacios al final
    while (fin >= inicio && esEspacio(texto[fin])) {
        fin--;
    }

    if (inicio > fin) {
        return "";  // el texto solo tenía espacios (o estaba vacío)
    }
    return texto.substr(inicio, fin - inicio + 1);
}

bool convertirAEntero(const string& texto, int& resultado) {
    string limpio = limpiarEspacios(texto);
    int n = limpio.size();

    // Máximo 9 dígitos para que el número siempre quepa en un int
    if (n == 0 || n > 9) {
        return false;
    }

    int valor = 0;
    for (int i = 0; i < n; i++) {
        char c = limpio[i];
        if (c < '0' || c > '9') {
            return false;  // encontramos una letra u otro símbolo
        }
        // Ejemplo con "305": 0*10+3 = 3 -> 3*10+0 = 30 -> 30*10+5 = 305
        valor = valor * 10 + (c - '0');
    }

    resultado = valor;
    return true;
}
