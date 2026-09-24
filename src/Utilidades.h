// Utilidades.h
// Funciones auxiliares para manejar texto que se usan en varios archivos
// (Registro, Ordenamientos, Busquedas y main). Se ponen aquí para no repetir
// el mismo código en cada módulo.

#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>

// Regresa una copia del texto con todas las letras en minúscula.
// Se usa para comparar nombres sin importar mayúsculas ("salah" == "Salah").
std::string aMinusculas(const std::string& texto);

// Regresa una copia del texto sin espacios, tabuladores ni saltos de línea
// al inicio y al final. También quita el '\r' que dejan los archivos
// creados en Windows.
std::string limpiarEspacios(const std::string& texto);

// Intenta convertir un texto a número entero NO negativo.
// Regresa true si lo logró (y guarda el número en 'resultado') o false si el
// texto está vacío o tiene algo que no sea dígito (por ejemplo "abc" o "12a").
// Se hace a mano en lugar de usar stoi para no tener que manejar excepciones.
bool convertirAEntero(const std::string& texto, int& resultado);

#endif
