#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

// ======================= ESTRUCTURAS ===========================
struct Juego {
    string nombre;
    int puntajeMaximo;
    Juego* siguiente;
};

struct Personaje {
    string nombre;
    int nivel;
    int xp;
    int xpNecesario;
    int palabrasAprendidas;
    int progreso[4];
};

// ======================= PROTOTIPOS ===========================
Juego* crearListaJuegos();
void verPerfil(const Personaje* pj);
void subirNivel(Personaje* pj);
void actualizarProgreso(Personaje* pj);
void mostrarResultados(Personaje* pj, int puntos, int juegoIndex);
int jugarModulo(const string& nombre);
void guardarPersonaje(const Personaje* pj);
void menuPrincipal(Personaje* pj, Juego* listaJuegos);

#endif

