#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <string>
using namespace std;

class Jugador {
private:
    string nombre;
    string equipo;
    string posicion;
    int edad;
    string nacionalidad;
    int partidosJugados;
    int partidosTitular;
    int minutos;
    int goles;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;

public:
    Jugador();

    // Constructor para buscar: crea un jugador que solo tiene nombre.
    // Como los operadores de abajo comparan solo el nombre, con eso basta
    // para buscarlo en la lista o en el árbol.
    Jugador(string nombre);

    Jugador(string nombre, string equipo, string posicion, int edad,
            string nacionalidad, int partidosJugados, int partidosTitular,
            int minutos, int goles, int asistencias,
            int tarjetasAmarillas, int tarjetasRojas);

    // Son "const" porque solo leen los atributos, no los cambian
    string getNombre() const;
    string getEquipo() const;
    string getPosicion() const;
    int getEdad() const;
    string getNacionalidad() const;
    int getPartidosJugados() const;
    int getPartidosTitular() const;
    int getMinutos() const;
    int getGoles() const;
    int getAsistencias() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;

    // Setters de las estadísticas (para la opción "Actualizar").
    // No hay setNombre: cambiar el nombre desacomodaría el árbol, que está
    // ordenado por nombre.
    void setPartidosJugados(int partidosJugados);
    void setPartidosTitular(int partidosTitular);
    void setMinutos(int minutos);
    void setGoles(int goles);
    void setAsistencias(int asistencias);
    void setTarjetasAmarillas(int tarjetasAmarillas);
    void setTarjetasRojas(int tarjetasRojas);

    // Atributo derivado: se calcula con goles y minutos, no se guarda
    double golesPor90Min() const;

    // Sobrecarga de operadores: es la pieza que conecta Jugador con los
    // templates. ListaDoble<T> y ArbolBST<T> no saben qué es un Jugador; solo
    // usan ==, <, > y << sobre el tipo T. Al definirlos aquí, un Jugador se
    // puede guardar, buscar y ordenar dentro de ellos.
    // Comparan SOLO el nombre y sin importar mayúsculas, por eso el árbol
    // queda en orden alfabético y "declan rice" encuentra a "Declan Rice".
    bool operator<(const Jugador& otro) const;
    bool operator>(const Jugador& otro) const;
    bool operator==(const Jugador& otro) const;
};

// Operador << : permite escribir "cout << jugador" e imprime una fila de la
// tabla. Va fuera de la clase porque a la izquierda está cout, no un Jugador.
// Regresa la misma salida para poder encadenar: cout << jugador << endl;
ostream& operator<<(ostream& salida, const Jugador& jugador);

#endif
