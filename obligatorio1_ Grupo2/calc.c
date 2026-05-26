#include <stdio.h>

int main() {
    // Variables principales
    int opcion;
    double a, b, resultado;
    double memoria = 0.0;
    double ultimo_resultado = 0.0;
    int hay_resultado = 0;  // 0 = no hay, 1 = sí hay

    int historial[100]; // Para almacenar las opciones seleccionadas
    int controladores[9] = {0}; // Para controlar el uso de cada opción
    int totalops = 0; // Contador de operaciones realizadas

    int i, j;
    int es_valido;
    int temp_int;
    char entrada[100];
 
    printf("Calculadora en C - Grupo 2\n");

    while (1) {
        printf("\nSeleccione una operación:\n");
        printf("1. Suma\n");
        printf("2. Resta\n");
        printf("3. Multiplicación\n");
        printf("4. División\n");
        printf("5. Potenciación\n");
        printf("6. Raíz cuadrada\n");
        printf("7. Memoria (M)\n");
        printf("8. Historial (H)\n");
        printf("9. Salir (S)\n");
        printf("Opción: ");
        
        // Validar entrada de opción
        es_valido = 0;
        while (!es_valido) {
            fgets(entrada, sizeof(entrada), stdin);
            if (sscanf(entrada, "%d", &temp_int) == 1 && temp_int >= 1 && temp_int <= 9) {
                opcion = temp_int;
                es_valido = 1;
            } else {
                printf("Entrada no válida. Por favor, ingrese un número entre 1 y 9: ");
            }
        }

        if (opcion == 9) {
            printf("Saliendo de la calculadora. ¡Hasta luego!\n");
            break;
        }

        // Almacenar la opción en el historial
        if (totalops < 100) {
            historial[totalops++] = opcion;
            controladores[opcion - 1]++;
        }

        switch (opcion) {
            case 1: // Suma
                printf("Ingrese el primer número: ");
                scanf("%lf", &a);
                printf("Ingrese el segundo número: ");
                scanf("%lf", &b);
                resultado = a + b;
                break;
            case 2: // Resta
                printf("Ingrese el primer número: ");
                scanf("%lf", &a);
                printf("Ingrese el segundo número: ");
                scanf("%lf", &b);
                resultado = a - b;
                break;
            case 3: // Multiplicación
                printf("Ingrese el primer número: ");
                scanf("%lf", &a);
                printf("Ingrese el segundo número: ");
                scanf("%lf", &b);
                resultado = a * b;
                break;
            case 4: // División
                printf("Ingrese el primer número: ");
                scanf("%lf", &a);
                printf("Ingrese el segundo número:) ");

        }
    }