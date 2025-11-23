#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 50
#define MAX_LINE_LENGTH 256

void limpiarPantalla(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void mostrarArchivoYEsperar(FILE *file) {
    char linea[MAX_LINE_LENGTH];

    // Colocar el puntero al inicio del archivo
    rewind(file);

    printf("Contenido de 'lenguaje.txt':\n\n");

    // Imprimir todo el archivo tal cual
    while (fgets(linea, sizeof(linea), file) != NULL) {
        printf("%s", linea);
    }

    // Esperar a que el usuario presione Enter
    printf("\n\nPulsa Enter para continuar...");
    // Consumir cualquier carácter pendiente en el buffer de entrada
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // nada, vaciando el buffer
    }
    // Ahora sí esperar Enter
    getchar();

    // Limpiar la pantalla y dejar el archivo listo para el juego
    limpiarPantalla();
    rewind(file);
}

int main() {
    FILE *file;
    char word1[MAX_WORD_LENGTH], word2[MAX_WORD_LENGTH];
    int puntos = 10;
    int totalPairs = 0;
    char respuesta[MAX_WORD_LENGTH];

    file = fopen("lenguaje.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    // Contar parejas
    while (fscanf(file, "%s\t%s", word1, word2) == 2) {
        totalPairs++;
    }
    rewind(file);

    if (totalPairs == 0) {
        printf("El archivo no contiene parejas de palabras.\n");
        fclose(file);
        return 1;
    }

    // Mostrar todo el contenido del archivo, esperar Enter y limpiar pantalla
    mostrarArchivoYEsperar(file);

    srand((unsigned int)time(NULL));

    while (1) {
        int randomIndex = rand() % totalPairs;
        int currentIndex = 0;

        rewind(file);
        while (fscanf(file, "%s\t%s", word1, word2) == 2) {
            if (currentIndex == randomIndex) {
                break;
            }
            currentIndex++;
        }

        printf("\nAdivina la pareja de la palabra: %s\n", word1);
        printf("Ingresa la palabra que crees que corresponde (o escribe 'salir' para terminar): ");
        scanf("%49s", respuesta);

        if (strcmp(respuesta, "salir") == 0) {
            printf("Juego terminado. Puntos finales: %d\n", puntos);
            break;
        }

        if (strcmp(respuesta, word2) == 0) {
            printf("¡Correcto!\n");
        } else {
            printf("Incorrecto. La respuesta correcta era: %s\n", word2);
            puntos -= 1;
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
