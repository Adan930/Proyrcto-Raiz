#include "game.h"

main() {
    srand(static_cast<unsigned int>(time(NULL)));

    Personaje jugador;
    cout << "Ingrese el nombre de su personaje: ";
    getline(cin, jugador.nombre);

    jugador.nivel = 1;
    jugador.xp = 0;
    jugador.xpNecesario = 100;
    jugador.palabrasAprendidas = 0;

    for (int i = 0; i < 4; i++)
        jugador.progreso[i] = 0;

    Juego* listaJuegos =  crearListaJuegos();

    menuPrincipal(&jugador, listaJuegos);

    while (listaJuegos != NULL) {
        Juego* temp = listaJuegos;
        listaJuegos = listaJuegos->siguiente;
        delete temp;
    }

    
}

