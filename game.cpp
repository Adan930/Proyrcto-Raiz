#include "game.h"

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

    int xpGanada = puntos / 2;
    int palabras = puntos / 10;

    cout << "XP ganada: " << xpGanada << endl;
    cout << "Palabras nuevas aprendidas: " << palabras << endl;

    pj->xp += xpGanada;
    pj->palabrasAprendidas += palabras;

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

void guardarPersonaje(const Personaje* pj) {
    FILE* archivo = fopen("personaje.txt", "a");
    if (!archivo) {
        cout << "Error al crear el archivo." << endl;
        return;
    }

    fprintf(archivo, "===== PERFIL DEL JUGADOR =====\n");
    fprintf(archivo, "Nombre: %s\n", pj->nombre.c_str());
    fprintf(archivo, "Nivel: %d\n", pj->nivel);
    fprintf(archivo, "Experiencia: %d/%d\n", pj->xp, pj->xpNecesario);
    fprintf(archivo, "Palabras aprendidas: %d\n", pj->palabrasAprendidas);
    fprintf(archivo, "Progreso:\n");
    fprintf(archivo, "Memoria: %d%%\n", pj->progreso[0]);
    fprintf(archivo, "Adivinanzas: %d%%\n", pj->progreso[1]);
    fprintf(archivo, "Traducción: %d%%\n", pj->progreso[2]);
    fprintf(archivo, "Trivia: %d%%\n", pj->progreso[3]);
    fprintf(archivo, "==============================\n");

    fclose(archivo);
    cout << "\nDatos guardados en 'personaje.txt'.\n";
}

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
            cout << "Entrada inválida.\n";
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

            if (seleccion < 1 || seleccion > 4) {
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
            cout << "Guardando datos y saliendo..." << endl;
            guardarPersonaje(pj);
            break;

        default:
            cout << "Opción inválida." << endl;
        }

    } while (opcion != 3);
}

