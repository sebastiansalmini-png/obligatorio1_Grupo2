#include <stdio.h>

int main() {
    int datos[100];
    int n = 0;
    int entrada;

    printf("========================================\n");
    printf("     ESTADISTICAS v1.0\n");
    printf("========================================\n");
    printf("Ingrese numeros enteros (0 termina, max 100):\n");

    while (n < 100) {
        printf("> ");
        if (scanf("%d", &entrada) != 1) {
            printf("Entrada invalida, ingrese un entero.\n");
            while (getchar() != '\n');
            continue;
        }
        if (entrada == 0) {
            break;
        }
        datos[n] = entrada;
        n++;
    }

    if (n == 0) {
        printf("Sin datos.\n");
        return 0;
    }

    /* --- Bubble sort ascendente --- */
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (datos[j] > datos[j + 1]) {
                temp = datos[j];
                datos[j] = datos[j + 1];
                datos[j + 1] = temp;
            }
        }
    }

    /* --- Cantidad, suma, promedio --- */
    long long suma = 0;
    for (i = 0; i < n; i++) {
        suma += datos[i];
    }
    double promedio = (double)suma / n;

    /* --- Minimo y maximo (ya ordenado) --- */
    int minimo = datos[0];
    int maximo = datos[n - 1];

    /* --- Mediana --- */
    double mediana;
    if (n % 2 == 1) {
        mediana = datos[n / 2];
    } else {
        mediana = (datos[n / 2 - 1] + datos[n / 2]) / 2.0;
    }

    /* --- Moda y frecuencias ---
       Como el arreglo esta ordenado, contamos rachas consecutivas.
       Guardamos valor unico y su frecuencia en paralelo.         */
    int unicos[100];
    int freqs[100];
    int num_unicos = 0;

    i = 0;
    while (i < n) {
        int val = datos[i];
        int cnt = 0;
        while (i < n && datos[i] == val) {
            cnt++;
            i++;
        }
        unicos[num_unicos] = val;
        freqs[num_unicos] = cnt;
        num_unicos++;
    }

    /* Moda: max frecuencia; empate -> el menor (ya esta ordenado -> primero) */
    int max_freq = 0;
    int moda = unicos[0];
    for (i = 0; i < num_unicos; i++) {
        if (freqs[i] > max_freq) {
            max_freq = freqs[i];
            moda = unicos[i];
        }
    }

    /* --- Duplicados: valores que aparecen mas de una vez --- */
    int duplicados = 0;
    for (i = 0; i < num_unicos; i++) {
        if (freqs[i] > 1) {
            duplicados++;
        }
    }

    /* --- Imprimir resultados --- */
    printf("\n=== RESULTADOS ===\n");
    printf("Cantidad : %d\n", n);
    printf("Suma     : %lld\n", suma);
    printf("Promedio : %.2f\n", promedio);
    printf("Min      : %d\n", minimo);
    printf("Max      : %d\n", maximo);
    printf("Mediana  : %.1f\n", mediana);
    printf("Moda     : %d (%d veces)\n", moda, max_freq);
    printf("Duplicados (valores con repeticion): %d\n", duplicados);

    /* --- Histograma ASCII --- */
    printf("\n=== HISTOGRAMA ===\n");

    /* Ancho maximo de barra: 40 columnas, escalado al max_freq */
    int max_barra = 40;

    for (i = 0; i < num_unicos; i++) {
        /* Calcular largo de barra proporcional */
        int largo = (freqs[i] * max_barra) / max_freq;
        if (largo == 0) largo = 1;   /* al menos una '#' si existe */

        printf("%5d | ", unicos[i]);
        for (j = 0; j < largo; j++) {
            printf("#");
        }
        printf(" %d\n", freqs[i]);
    }

    return 0;
}