#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 50

int main() {
    FILE *file;
    char word1[MAX_WORD_LENGTH], word2[MAX_WORD_LENGTH];
    int puntos = 10; // Contador inicial
    int totalPairs = 0;
    char respuesta[MAX_WORD_LENGTH];

    // Abrimos el archivo en modo lectura
    file = fopen("lenguaje.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    // Contar cuántas parejas hay en el archivo
    while (fscanf(file, "%s\t%s", word1, word2) == 2) {
        totalPairs++;
    }
    rewind(file); // Volvemos al inicio del archivo

    if (totalPairs == 0) {
        printf("El archivo no contiene parejas de palabras.\n");
        fclose(file);
        return 1;
    }

    srand(time(NULL));

    while (1) {
        // Leer la pareja seleccionada aleatoriamente
        int randomIndex = rand() % totalPairs;
        int currentIndex = 0;

        rewind(file);
        while (fscanf(file, "%s\t%s", word1, word2) == 2) {
            if (currentIndex == randomIndex) {
                break;
            }
            currentIndex++;
        }

        // Mostrar la palabra y solicitar respuesta
        printf("\nAdivina la pareja de la palabra: %s\n", word1);
        printf("Ingresa la palabra que crees que corresponde (o escribe 'salir' para terminar): ");
        scanf("%s", respuesta);

        // Opción de salida
        if (strcmp(respuesta, "salir") == 0) {
            printf("Juego terminado. Puntos finales: %d\n", puntos);
            break;
        }

        // Verificar respuesta
        if (strcmp(respuesta, word2) == 0) {
            printf("¡Correcto!\n");
            // Puntos no se modifican
        } else {
            printf("Incorrecto. La respuesta correcta era: %s\n", word2);
            puntos -= 1; // Se resta un punto
        }

        printf("Puntos actuales: %d\n", puntos);
        if (puntos <= 0) {
            printf("Has llegado a 0 puntos. Fin del juego.\n");
            break;
        }
    }

    fclose(file);
    return 0;
}
