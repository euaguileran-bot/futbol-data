#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <vector>
#include "Jugador.h"
#include "ListaDoble.h"
#include "ArbolBST.h"

// n = jugadores, h = altura del árbol, e = equipos, p = posiciones
class Registro {
private:
    ListaDoble<Jugador> lista;   // almacenamiento principal (en orden de carga)
    ArbolBST<Jugador> arbol;     // índice por nombre para buscar rápido
    vector<string> equipos;      // leídos de data/equipos.txt
    vector<string> posiciones;   // leídos de data/posiciones.txt

    bool leerCatalogo(string ruta, vector<string>& destino);
    bool estaEnCatalogo(string valor, const vector<string>& catalogo) const;
    void reconstruirArbol();
    void mostrarEncabezado() const;
    void mostrarPie(int mostrados) const;

public:
    // Catálogos (se cargan al iniciar el programa)
    bool cargarCatalogos(string rutaEquipos, string rutaPosiciones);
    vector<string> getEquipos() const;
    vector<string> getPosiciones() const;

    // Regresa cuántos jugadores se cargaron (0 si hubo un error)
    int cargarDesdeCSV(string ruta);

    // Mostrar
    void mostrarOrdenDeCarga() const;
    void mostrarOrdenInverso() const;
    void mostrarAlfabetico() const;
    void mostrarLista(const vector<Jugador>& jugadores, int cantidad) const;   // 0 = todos

    vector<Jugador> getJugadores() const;
    int getCantidad() const;
    int getCantidadEnArbol() const;

    // Consultas
    int buscarEnLista(string nombre, Jugador& encontrado, int& pasos) const;
    bool buscarEnArbol(string nombre, Jugador& encontrado, int& pasos) const;
    bool existeJugador(string nombre) const;

    // Cambios (siempre dejan la lista y el árbol sincronizados)
    bool agregarJugador(const Jugador& nuevo, bool alInicio);
    bool actualizarJugador(const Jugador& actualizado);
    bool eliminarJugador(string nombre);

    // Información del árbol
    int alturaArbol() const;
    void mostrarRecorrido(int tipo) const;   // 1 pre, 2 in, 3 post, 4 por niveles
    int nivelDe(string nombre) const;
    vector<Jugador> ancestrosDe(string nombre) const;

    // Filtros (sobre una copia de la lista)
    vector<Jugador> filtrarPorEquipo(string equipo) const;
    vector<Jugador> filtrarPorPosicion(string posicion) const;
    vector<Jugador> filtrarPorRangoGoles(int minimo, int maximo) const;
};

#endif
