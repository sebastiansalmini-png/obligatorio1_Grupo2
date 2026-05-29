#include <stdio.h>

#define N_MAX 20

int main() {
    int n;
    int i, j;

    printf("========================================\n");
    printf("     FIGURAS HUECAS v1.0\n");
    printf("========================================\n");

    /* Validar n entre 3 y 20 */
    do {
        printf("Ingrese altura n (3-20): ");
        if (scanf("%d", &n) != 1) {
            printf("Entrada invalida.\n");
            while (getchar() != '\n');
            n = 0;
            continue;
        }
        if (n < 3 || n > 20) {
            printf("Error: n debe estar entre 3 y 20.\n");
        }
    } while (n < 3 || n > 20);

    /* =========================================
       FIGURA 1: PIRAMIDE HUECA
       Ancho de la base = 2*n - 1
       Usamos una matriz de n filas x (2n-1) columnas
       ========================================= */
    int ancho_pir = 2 * n - 1;
    char pir[N_MAX][2 * N_MAX - 1];

    /* Inicializar con espacios */
    for (i = 0; i < n; i++) {
        for (j = 0; j < ancho_pir; j++) {
            pir[i][j] = ' ';
        }
    }

    /* Rellenar borde de la piramide */
    for (i = 0; i < n; i++) {
        int espacios = n - 1 - i;          /* espacios a la izquierda */
        int izq = espacios;                 /* columna izquierda de esta fila */
        int der = ancho_pir - 1 - espacios; /* columna derecha */

        if (i == 0) {
            /* Cima: solo un '*' */
            pir[i][izq] = '*';
        } else if (i == n - 1) {
            /* Base: toda de '*' */
            for (j = 0; j < ancho_pir; j++) {
                pir[i][j] = '*';
            }
        } else {
            /* Filas intermedias: solo los extremos */
            pir[i][izq] = '*';
            pir[i][der] = '*';
        }
    }

    printf("\n--- Piramide hueca (n = %d) ---\n", n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < ancho_pir; j++) {
            printf("%c", pir[i][j]);
        }
        printf("\n");
    }

    /* =========================================
       FIGURA 2: ROMBO HUECO
       Altura total = 2*n - 1 filas
       Ancho maximo = 2*n - 1 (en la fila central)
       ========================================= */
    int alto_rombo = 2 * n - 1;
    int ancho_rombo = 2 * n - 1;
    char rombo[2 * N_MAX - 1][2 * N_MAX - 1];

    /* Inicializar con espacios */
    for (i = 0; i < alto_rombo; i++) {
        for (j = 0; j < ancho_rombo; j++) {
            rombo[i][j] = ' ';
        }
    }

    /* Rellenar borde del rombo fila por fila */
    for (i = 0; i < alto_rombo; i++) {
        /* Distancia a la fila central */
        int dist = i < n ? (n - 1 - i) : (i - n + 1);

        int izq = dist;
        int der = ancho_rombo - 1 - dist;

        if (izq == der) {
            /* Cima o base: un solo '*' */
            rombo[i][izq] = '*';
        } else {
            /* Filas intermedias: solo extremos (hueco) */
            rombo[i][izq] = '*';
            rombo[i][der] = '*';
        }
    }

    printf("\n--- Rombo hueco (n = %d) ---\n", n);
    for (i = 0; i < alto_rombo; i++) {
        for (j = 0; j < ancho_rombo; j++) {
            printf("%c", rombo[i][j]);
        }
        printf("\n");
    }

    return 0;
}