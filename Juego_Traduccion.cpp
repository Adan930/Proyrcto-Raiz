#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// ---------------- MINIJUEGO: TRADUCCIÓN RÁPIDA ---------------- //

void jugarTraduccionRapida() {
    const int N = 10;
    const char *nahuatl[N] = {
        "atl", "xochitl", "calli", "tlalli", "tepetl",
        "metztli", "citlalli", "cualli", "tletl", "tlakatl"
    };
    const char *espanol[N] = {
        "agua", "flor", "casa", "tierra", "cerro",
        "luna", "estrella", "bueno", "fuego", "hombre"
    };

    int preguntas = 6;
    if (preguntas > N) preguntas = N;

    int indices[N];
    for (int i = 0; i < N; i++) indices[i] = i;

    srand(time(NULL));
    // Mezclar preguntas
    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    const double tiempoLimite = 8.0; // segundos por pregunta
    int totalAciertos = 0;
    int totalFallos = 0;
    double sumaTiempos = 0.0;
    int puntosTotales = 0;

    printf("\n=== MINIJUEGO: TRADUCCION RAPIDA ===\n");
    printf("Responde %d preguntas. Tienes %.0f segundos por pregunta.\n", preguntas, tiempoLimite);
    printf("Premio: puntos por acierto + bonus por rapidez.\n\n");

    for (int q = 0; q < preguntas; q++) {
        int idxCorrecto = indices[q];

        // Crear opciones (1 correcta + 3 falsas)
        int opcionesIdx[4];
        opcionesIdx[0] = idxCorrecto;
        int llenadas = 1;
        while (llenadas < 4) {
            int cand = rand() % N;
            int repetido = 0;
            for (int k = 0; k < llenadas; k++)
                if (opcionesIdx[k] == cand) repetido = 1;
            if (!repetido) opcionesIdx[llenadas++] = cand;
        }

        // Mezclar opciones
        for (int i = 3; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = opcionesIdx[i];
            opcionesIdx[i] = opcionesIdx[j];
            opcionesIdx[j] = temp;
        }

        printf("Pregunta %d: Que significa '%s' en espanol?\n", q + 1, nahuatl[idxCorrecto]);
        for (int i = 0; i < 4; i++) {
            printf("  %d) %s\n", i + 1, espanol[opcionesIdx[i]]);
        }

        printf("Tu respuesta (1-4): ");
        clock_t inicio = clock();
        int respuesta;
        scanf("%d", &respuesta);
        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        sumaTiempos += tiempo;

        if (tiempo > tiempoLimite) {
            printf("? Tiempo agotado (%.1f s). Respuesta no valida.\n", tiempo);
            totalFallos++;
        } else if (respuesta < 1 || respuesta > 4) {
            printf("? Opcion invalida.\n");
            totalFallos++;
        } else {
            int elegidoIdx = opcionesIdx[respuesta - 1];
            if (elegidoIdx == idxCorrecto) {
                int puntosBase = 100;
                int bonus = (int)fmax(0, (tiempoLimite - tiempo) * 20);
                int puntos = puntosBase + bonus;
                puntosTotales += puntos;
                totalAciertos++;
                printf("? Correcto. +%d puntos (bonus: %d)\n", puntosBase, bonus);
            } else {
                printf("? Incorrecto. Era '%s'.\n", espanol[idxCorrecto]);
                totalFallos++;
            }
        }

        printf("Tiempo usado: %.1f s\n", tiempo);
        printf("-----------------------------------\n");
    }

    double promedio = (preguntas > 0) ? (sumaTiempos / preguntas) : 0.0;

    printf("\n=== RESULTADOS FINALES ===\n");
    printf("Aciertos: %d\n", totalAciertos);
    printf("Fallos: %d\n", totalFallos);
    printf("Tiempo promedio: %.2f s\n", promedio);
    printf("Puntaje total: %d\n", puntosTotales);
    printf("===========================\n");
}

// ---------------- PROGRAMA PRINCIPAL ---------------- //

int main() {
    jugarTraduccionRapida();
    return 0;
}

