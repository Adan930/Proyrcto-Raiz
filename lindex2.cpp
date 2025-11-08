#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdio> // ? Para fopen, fprintf, fclose
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
    Juego* primero = NULL;
    Juego* ultimo = NULL;
    string nombres[4] = {"Memoria", "Adivinanzas", "Traducción", "Trivia"};

    for (int i = 0; i < 4; i++) {
        Juego* nuevo = new Juego;
        nuevo->nombre = nombres[i];
        nuevo->puntajeMaximo = 0;
        nuevo->siguiente = NULL;

        if (primero == NULL)
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

void subirNivel(Personaje* pj) {
    pj->nivel++;
    pj->xp -= pj->xpNecesario;
    pj->xpNecesario += 100;
    cout << "\n¡Has subido al nivel " << pj->nivel << "!" << endl;
    cout << "Nuevas habilidades desbloqueadas." << endl;
}

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

int jugarModulo(const string& nombre) {
    cout << "\nJugando: " << nombre << "..." << endl;
    int puntos = rand() % 200 + 50;
    return puntos;
}

// ? NUEVA FUNCIÓN: guarda los datos usando fopen/fprintf/fclose
void guardarPersonaje(const Personaje* pj) {
    FILE* archivo = fopen("personaje.txt", "a"); // crea o reemplaza el archivo
    if (archivo == NULL) {
        cout << "Error al crear el archivo de personaje." << endl;
        return;
    }

    fprintf(archivo, "===== PERFIL DEL JUGADOR =====\n");
    fprintf(archivo, "Nombre: %s\n", pj->nombre.c_str());
    fprintf(archivo, "Nivel: %d\n", pj->nivel);
    fprintf(archivo, "Experiencia: %d/%d\n", pj->xp, pj->xpNecesario);
    fprintf(archivo, "Palabras aprendidas: %d\n", pj->palabrasAprendidas);
    fprintf(archivo, "Progreso por juego:\n");
    fprintf(archivo, "1. Memoria: %d%%\n", pj->progreso[0]);
    fprintf(archivo, "2. Adivinanzas: %d%%\n", pj->progreso[1]);
    fprintf(archivo, "3. Traducción: %d%%\n", pj->progreso[2]);
    fprintf(archivo, "4. Trivia: %d%%\n", pj->progreso[3]);
    fprintf(archivo, "==============================\n");

    fclose(archivo);
    cout << "\n? Datos del personaje guardados en 'personaje.txt'.\n";
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
            while (actual != NULL) {
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
            cout << "\nSaliendo del sistema..." << endl;
            guardarPersonaje(pj); // ? guarda al salir
            break;
        default:
            cout << "Opción no válida." << endl;
        }

    } while (opcion != 3);
}

// ======================= PROGRAMA PRINCIPAL ===========================

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

    Juego* listaJuegos = crearListaJuegos();

    menuPrincipal(&jugador, listaJuegos);

    while (listaJuegos != NULL) {
        Juego* temp = listaJuegos;
        listaJuegos = listaJuegos->siguiente;
        delete temp;
    }

}

