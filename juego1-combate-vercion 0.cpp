#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- ESTRUCTURAS DEL JUEGO DE COMBATE ---

typedef struct {
    char palabraEspanol[30];
    char palabraIndigena[30];
    int danio;
} Hechizo;

typedef struct {
    char nombre[30];
    int vidaActual;
    int vidaMax;
    int ataqueBase;
} Enemigo;

// Usaremos una versión simplificada del Personaje gerado el el archivo origen o index
typedef struct {
    char nickname[20];
    int vidaActual;
    int vidaMax;
    int experienciaGanada;
} JugadorBatalla;


void limpiarBufferCombate() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausarCombate() {
    printf("\nPresione Enter para continuar...");
    limpiarBufferCombate();
    getchar();
}

// --- LÓGICA DEL JUEGO DE COMBATE ---

//Pendinte, agregar mas cantidad de enemigos segun el Progeso de los dema, tematicas y vocabulario
Enemigo crearEnemigo(int nivelDificultad) {
    Enemigo e;
    if (nivelDificultad == 1) {
        strcpy(e.nombre, "Espitiru del Olvido");
        e.vidaMax = 100;
        e.vidaActual = 100;
        e.ataqueBase = 10;
    } else {
        strcpy(e.nombre, "Ignorancia Antigua");
        e.vidaMax = 200;
        e.vidaActual = 200;
        e.ataqueBase = 25;
    }
    return e;
}

// Cargar algunos hechizos de prueba , con intencion de que sean tomdaso despues de un archivo. txt
void cargarHechizosPrueba(Hechizo lista[], int *cantidad) {
    strcpy(lista[0].palabraEspanol, "Fuego");
    strcpy(lista[0].palabraIndigena, "Tletl"); // Náhuatl
    lista[0].danio = 30;

    strcpy(lista[1].palabraEspanol, "Agua");
    strcpy(lista[1].palabraIndigena, "Atl"); // Náhuatl
    lista[1].danio = 25;

    strcpy(lista[2].palabraEspanol, "Viento");
    strcpy(lista[2].palabraIndigena, "Ehecatl"); // Náhuatl
    lista[2].danio = 20;
    
    *cantidad = 3;
}

// Función principal del minijuego 
int iniciarCombate(char *nicknameJugador) {
    JugadorBatalla jugador;
    strcpy(jugador.nickname, nicknameJugador);
    jugador.vidaMax = 100; // Esto debería venir en base al el nivel del peroonaje y su cantiad de puntos obtenidos por jugar otras cosas
    jugador.vidaActual = jugador.vidaMax;
    jugador.experienciaGanada = 0;

    Enemigo enemigo = crearEnemigo(1); // Nivel 1 por defecto, deveria de aumentar segun el nivel de dificultad que se selecionara 
    //por el nivel del jugador
    
    Hechizo grimoire[10];
    int totalHechizos = 0;
    cargarHechizosPrueba(grimoire, &totalHechizos);//ataques de prueva

    int turno = 1;
    int opcionHechizo;
    char respuestaUsuario[30];

    printf("\n=== INICIANDO COMBATE ===\n");
    printf("Un %s salvaje ha aparecidodo \n", enemigo.nombre);
    pausarCombate();

    // Bucle principal de la batalla
    while (jugador.vidaActual > 0 && enemigo.vidaActual > 0) {
        printf("\n--- TURNO %d ---\n", turno);
        printf("[%s] HP: %d/%d\n", jugador.nickname, jugador.vidaActual, jugador.vidaMax);//simpre mostrando esto en timpo real y en cada 
        //turno 
        printf("[%s] HP: %d/%d\n", enemigo.nombre, enemigo.vidaActual, enemigo.vidaMax);
        printf("----------------\n");

        // Turno del Jugador
        printf("¡Es tu turno! Elige un hechizo (palabra a traducir):\n");
        for(int i = 0; i < totalHechizos; i++) {
            printf("%d. %s (Daño potencial: %d)\n", i+1, grimoire[i].palabraEspanol, grimoire[i].danio);
        }
        printf("Opción: ");
        scanf("%d", &opcionHechizo);
        limpiarBufferCombate();

        if (opcionHechizo < 1 || opcionHechizo > totalHechizos) {
            printf("¡Te tropezaste! Perdiste tu turno por elegir una opcion invalida.\n");
        } else {
            int indice = opcionHechizo - 1;
            printf("\nPara lanzar el hechizo de '%s', escribe su traduccion en Nahuatl:\n> ", grimoire[indice].palabraEspanol);
            fgets(respuestaUsuario, 30, stdin);
            respuestaUsuario[strcspn(respuestaUsuario, "\n")] = 0; // Eliminar salto de línea

            // Verificación simple (ignorando mayúsculas/minúsculas para facilitar)
            if (strcasecmp(respuestaUsuario, grimoire[indice].palabraIndigena) == 0) {
                printf("\n¡CORRECTO! ¡Lanzaste %s!\n", grimoire[indice].palabraIndigena);
                printf("Causas %d puntos de daño a %s.\n", grimoire[indice].danio, enemigo.nombre);
                enemigo.vidaActual -= grimoire[indice].danio;
            } else {
                printf("\n¡FATASTE! La palabra correcta era '%s'.\n", grimoire[indice].palabraIndigena);
                printf("El hechizo explota en tu cara, recibes 5 de daño.\n");
                jugador.vidaActual -= 5;
            }
        }
        
        // Verificar si el enemigo murió antes de su turno
        if (enemigo.vidaActual <= 0) break;

        pausarCombate();

        // Turno del Enemigo
        printf("\n--- Turno del Enemigo ---\n");
        printf("%s te ataca y causa %d de daño!\n", enemigo.nombre, enemigo.ataqueBase);
        jugador.vidaActual -= enemigo.ataqueBase;
        pausarCombate();

        turno++;
    }

    // Fin del combate
    system("cls");
    if (jugador.vidaActual > 0) {
        printf("\n¡VICTORIA!\n");
        printf("Has derrotado a %s.\n", enemigo.nombre);
        jugador.experienciaGanada = 50; // Valor de ejemplo
        printf("Ganas %d puntos de experiencia.\n", jugador.experienciaGanada);
        return jugador.experienciaGanada; // RetornaEXP o puntaje anado durante el combate
    } else {
        printf("\nDERROTA...\n");
        printf("%s te ha vencido.Pierdes TU .\n", enemigo.nombre);
        return 0;
    }
}

// MAIN DE PRUEBA PARA EL JUEGO 1
// (Esto lo quitarás cuando lo integres a tu main principal)
int main() {
    int expGanada = iniciarCombate("GuerreroJaguar");
    printf("\n[DEBUG] Combate terminado. EXP retornada al menú principal: %d\n", expGanada);
    return 0;
}
