// Registro.h
// Clase que guarda a todos los jugadores cargados desde el CSV y ofrece
// operaciones para mostrarlos, filtrarlos y exportarlos.

#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <vector>
#include "Jugador.h"

class Registro {
private:
    std::vector<Jugador> jugadores;   // todos los jugadores cargados del archivo

public:
    // Abre el archivo CSV, lo lee línea por línea y valida cada registro.
    // Regresa cuántos jugadores se cargaron (0 si no se pudo abrir el archivo
    // o si ninguna línea era válida; en ese caso se conservan los datos anteriores).
    int cargarDesdeCSV(const std::string& ruta);

    // Muestra en forma de tabla todos los jugadores cargados
    void mostrarTodos() const;

    // Muestra en forma de tabla cualquier lista de jugadores.
    // Si 'limite' es 0 (o mayor que la lista) se muestran todos.
    void mostrarLista(const std::vector<Jugador>& lista, int limite) const;

    // Regresa el vector de jugadores para usarlo con Ordenamientos y Busquedas.
    // Se regresa como referencia constante: no se copia y nadie puede modificarlo.
    const std::vector<Jugador>& getJugadores() const;

    // Cantidad de jugadores cargados
    int getCantidad() const;

    // Filtros por texto (no distinguen mayúsculas de minúsculas).
    // Cada uno regresa un NUEVO vector; el registro original no cambia.
    std::vector<Jugador> filtrarPorEquipo(const std::string& equipo) const;
    std::vector<Jugador> filtrarPorPosicion(const std::string& posicion) const;
    std::vector<Jugador> filtrarPorNacionalidad(const std::string& nacionalidad) const;

    // Filtros por rango numérico (incluyen los extremos: minimo <= valor <= maximo)
    std::vector<Jugador> filtrarPorRangoGoles(int minimo, int maximo) const;
    std::vector<Jugador> filtrarPorRangoAsistencias(int minimo, int maximo) const;
    std::vector<Jugador> filtrarPorRangoEdad(int minimo, int maximo) const;
    std::vector<Jugador> filtrarPorRangoMinutos(int minimo, int maximo) const;

    // Escribe 'datos' en un nuevo archivo CSV con la misma cabecera que el
    // original (así el archivo exportado se puede volver a cargar).
    // Regresa true si se pudo escribir el archivo.
    bool exportarACSV(const std::string& ruta, const std::vector<Jugador>& datos) const;
};

#endif
