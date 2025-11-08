#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
// #include <cstddef> // No es estrictamente necesaria aquí, pero no hace daño.
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

// ======================= FUNCIONES DEL SISTEMA ===========================

Juego* crearListaJuegos() {
    Juego* primero = NULL; // CAMBIO: nullptr -> NULL
    Juego* ultimo = NULL;  // CAMBIO: nullptr -> NULL
    string nombres[4] = {"Memoria", "Adivinanzas", "Traducción", "Trivia"};

    for (int i = 0; i < 4; i++) {
        Juego* nuevo = new Juego;
        nuevo->nombre = nombres[i];
        nuevo->puntajeMaximo = 0;
        nuevo->siguiente = NULL; // CAMBIO: nullptr -> NULL

        if (primero == NULL) // CAMBIO: nullptr -> NULL
            primero = nuevo;
        else
            ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }

    return primero;
}

void verPerfil(const Personaje* pj) {
    cout << "\n===== PERFIL DEL JUGADOR =====" << endl;
    cout << "Nombre: " << pj->nombre << endl;
    cout << "Nivel: " << pj->nivel << endl;
    cout << "Experiencia: " << pj->xp << "/" << pj->xpNecesario << endl;
    cout << "Palabras aprendidas: " << pj->palabrasAprendidas << endl;
    cout << "Progreso por juego:" << endl;
    cout << "1. Memoria: " << pj->progreso[0] << "%" << endl;
    cout << "2. Adivinanzas: " << pj->progreso[1] << "%" << endl;
    cout << "3. Traducción: " << pj->progreso[2] << "%" << endl;
    cout << "4. Trivia: " << pj->progreso[3] << "%" << endl;
    cout << "==============================\n" << endl;
}

// Subir nivel del personaje
void subirNivel(Personaje* pj) {
    pj->nivel++;
    pj->xp -= pj->xpNecesario; // Conserva la experiencia sobrante
    pj->xpNecesario += 100;
    cout << "\n¡Has subido al nivel " << pj->nivel << "!" << endl;
    cout << "Nuevas habilidades desbloqueadas." << endl;
}

// Actualizar progreso después de jugar
void actualizarProgreso(Personaje* pj) {
    while (pj->xp >= pj->xpNecesario) {
        subirNivel(pj);
    }
}

void mostrarResultados(Personaje* pj, int puntos, int juegoIndex) {
    cout << "\n--- RESULTADOS DEL JUEGO ---" << endl;
    cout << "Puntaje obtenido: " << puntos << endl;
    cout << "XP ganada: " << puntos / 2 << endl;
    cout << "Palabras nuevas aprendidas: " << puntos / 10 << endl;

    pj->xp += puntos / 2;
    pj->palabrasAprendidas += puntos / 10;
    pj->progreso[juegoIndex] += puntos / 5;
    if (pj->progreso[juegoIndex] > 100)
        pj->progreso[juegoIndex] = 100;

    cout << "------------------------------" << endl;
}

// Simulación del módulo de juego
int jugarModulo(const string& nombre) {
    cout << "\nJugando: " << nombre << "..." << endl;
    int puntos = rand() % 200 + 50; // puntaje aleatorio entre 50 y 250
    return puntos;
}

// ======================= MENÚ PRINCIPAL ===========================

void menuPrincipal(Personaje* pj, Juego* listaJuegos) {
    int opcion;
    do {
        cout << "\n===== MENU PRINCIPAL =====" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Ver perfil" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada no válida. Intente de nuevo.\n";
            continue;
        }

        switch (opcion) {
        case 1: {
            cout << "\n--- Seleccione un juego ---" << endl;
            Juego* actual = listaJuegos;
            int i = 1;
            while (actual != NULL) { // CAMBIO: nullptr -> NULL
                cout << i << ". " << actual->nombre << " (Record: " << actual->puntajeMaximo << ")" << endl;
                actual = actual->siguiente;
                i++;
            }

            int seleccion;
            cout << "Opcion: ";
            cin >> seleccion;

            if (cin.fail() || seleccion < 1 || seleccion > 4) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Opción inválida." << endl;
                break;
            }

            Juego* temp = listaJuegos;
            for (int j = 1; j < seleccion; j++)
                temp = temp->siguiente;

            int puntos = jugarModulo(temp->nombre);
            mostrarResultados(pj, puntos, seleccion - 1);
            actualizarProgreso(pj);

            if (puntos > temp->puntajeMaximo)
                temp->puntajeMaximo = puntos;
            break;
        }
        case 2:
            verPerfil(pj);
            break;
        case 3:
            cout << "Saliendo del sistema..." << endl;
            break;
        default:
            cout << "Opción no válida." << endl;
        }

    } while (opcion != 3);
}

// ======================= PROGRAMA PRINCIPAL ===========================

int main() {
    // CAMBIO: nullptr -> NULL en time()
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

    Juego* listaJuegos = crearListaJuegos();

    menuPrincipal(&jugador, listaJuegos);

    // Liberar memoria
    while (listaJuegos != NULL) { // CAMBIO: nullptr -> NULL
        Juego* temp = listaJuegos;
        listaJuegos = listaJuegos->siguiente;
        delete temp;
    }

    return 0;
}
