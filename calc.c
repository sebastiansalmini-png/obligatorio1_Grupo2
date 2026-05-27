#include <stdio.h>
//Lo que pide el PDF
//Menú 1..9	Menú 0..8 + M+, M-, MR, MC, H
//Raíz cuadrada	Factorial, Primo, MCD
//Historial de 100	Historial circular de 20
//Sin memoria	M+, M-, MR, MC0
//Sin contadores por tipo	contadores[9]
int main() {
    // Variables principales
    int opcion;
    double a, b, resultado;
    double memoria = 0.0;
    double ultimo_resultado = 0.0;
    int hay_resultado = 0;  // 0 = no hay, 1 = sí hay
    
    // Historial circular (últimas 20 operaciones)
    int historial[20];      // ¡20, no 100!
    int contadores[9] = {0}; // índices 1..8, índice 0 sin usar
    int total_ops = 0;       // total acumulado
    
    int i;
    int es_valido;
    int temp_int;
    char entrada[100];
    char cmd[10];
    
    printf("========================================\n");
    printf("     CALCULADORA v1.0\n");
    printf("========================================\n");
    
    while (1) {
        // Mostrar menú según el PDF
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1) Suma\n");
        printf("2) Resta\n");
        printf("3) Multiplicacion\n");
        printf("4) Division y Modulo\n");
        printf("5) Potencia entera\n");
        printf("6) Factorial\n");
        printf("7) ¿Es primo?\n");
        printf("8) MCD (Euclides)\n");
        printf("M+) Sumar ultimo resultado a memoria\n");
        printf("M-) Restar ultimo resultado de memoria\n");
        printf("MR) Mostrar memoria\n");
        printf("MC) Borrar memoria\n");
        printf("H) Historial y estadisticas\n");
        printf("0) Salir\n");
        printf("Opcion> ");
        
        // Leer entrada (puede ser número o comando de letra)
        fgets(entrada, sizeof(entrada), stdin);
        
        // Verificar si es comando de letra (M+, M-, MR, MC, H)
        if (entrada[0] == 'M' || entrada[0] == 'm' || entrada[0] == 'H' || entrada[0] == 'h') {
            // Limpiar el salto de línea
            for (i = 0; entrada[i] != '\0'; i++) {
                if (entrada[i] == '\n') entrada[i] = '\0';
            }
            
            // Comandos de memoria
            if (entrada[0] == 'M' || entrada[0] == 'm') {
                if (entrada[1] == '+' && entrada[2] == '\0') {
                    if (hay_resultado) {
                        memoria += ultimo_resultado;
                        printf("Memoria: %.2f (se sumo %.2f)\n", memoria, ultimo_resultado);
                    } else {
                        printf("Error: No hay resultado previo para sumar a memoria.\n");
                    }
                }
                else if (entrada[1] == '-' && entrada[2] == '\0') {
                    if (hay_resultado) {
                        memoria -= ultimo_resultado;
                        printf("Memoria: %.2f (se resto %.2f)\n", memoria, ultimo_resultado);
                    } else {
                        printf("Error: No hay resultado previo para restar de memoria.\n");
                    }
                }
                else if (entrada[1] == 'R' && entrada[2] == '\0') {
                    printf("Memoria actual: %.2f\n", memoria);
                }
                else if (entrada[1] == 'C' && entrada[2] == '\0') {
                    memoria = 0.0;
                    printf("Memoria borrada (0.00)\n");
                }
                else {
                    printf("Comando no valido. Use M+, M-, MR o MC\n");
                }
            }
            else if (entrada[0] == 'H' || entrada[0] == 'h') {
                // Mostrar historial
                printf("\n=== HISTORIAL (ultimas 20 ops) ===\n");
                int inicio;
                if (total_ops < 20) {
                    inicio = 0;
                } else {
                    inicio = total_ops % 20;
                }
                
                for (i = 0; i < (total_ops < 20 ? total_ops : 20); i++) {
                    int idx = (inicio + i) % 20;
                    printf("[%02d] ", i+1);
                    switch(historial[idx]) {
                        case 1: printf("Suma"); break;
                        case 2: printf("Resta"); break;
                        case 3: printf("Multiplicacion"); break;
                        case 4: printf("Division"); break;
                        case 5: printf("Potencia"); break;
                        case 6: printf("Factorial"); break;
                        case 7: printf("Primo"); break;
                        case 8: printf("MCD"); break;
                    }
                    printf("\n");
                }
                
                printf("\n=== FRECUENCIA POR OPERACION ===\n");
                for (i = 1; i <= 8; i++) {
                    if (contadores[i] > 0) {
                        printf("Operacion %d: ", i);
                        switch(i) {
                            case 1: printf("Suma"); break;
                            case 2: printf("Resta"); break;
                            case 3: printf("Multiplicacion"); break;
                            case 4: printf("Division"); break;
                            case 5: printf("Potencia"); break;
                            case 6: printf("Factorial"); break;
                            case 7: printf("Primo"); break;
                            case 8: printf("MCD"); break;
                        }
                        printf(" -> %d veces\n", contadores[i]);
                    }
                }
                printf("Memoria actual: %.2f\n", memoria);
                printf("Total operaciones: %d\n", total_ops);
            }
            continue;  // Volver al inicio del menú
        }
        
        // Si no es comando de letra, intentar leer como número
        if (sscanf(entrada, "%d", &opcion) != 1) {
            printf("Opcion no valida. Use 0-8, M+, M-, MR, MC o H.\n");
            continue;
        }
        
        // Opción 0: Salir
        if (opcion == 0) {
            // Calcular operación más usada
            int max_ops = 0;
            int op_mas_usada = 0;
            for (i = 1; i <= 8; i++) {
                if (contadores[i] > max_ops) {
                    max_ops = contadores[i];
                    op_mas_usada = i;
                }
            }
            printf("\nOperaciones realizadas: %d\n", total_ops);
            if (max_ops > 0) {
                printf("Mas usada: ");
                switch(op_mas_usada) {
                    case 1: printf("Suma"); break;
                    case 2: printf("Resta"); break;
                    case 3: printf("Multiplicacion"); break;
                    case 4: printf("Division"); break;
                    case 5: printf("Potencia"); break;
                    case 6: printf("Factorial"); break;
                    case 7: printf("Primo"); break;
                    case 8: printf("MCD"); break;
                }
                printf(" (%d veces)\n", max_ops);
            }
            printf("¡Adios!\n");
            break;
        }
        
        // Validar opción numérica (1..8)
        if (opcion < 1 || opcion > 8) {
            printf("Opcion no valida. Use 0-8, M+, M-, MR, MC o H.\n");
            continue;
        }
        
        // Leer operandos según la operación
        es_valido = 1;
        
        switch(opcion) {
            case 1:  // Suma
                printf("Ingrese a: ");
                scanf("%lf", &a);
                printf("Ingrese b: ");
                scanf("%lf", &b);
                resultado = a + b;
                printf("Resultado: %.2f + %.2f = %.2f\n", a, b, resultado);
                break;
                
            case 2:  // Resta
                printf("Ingrese a: ");
                scanf("%lf", &a);
                printf("Ingrese b: ");
                scanf("%lf", &b);
                resultado = a - b;
                printf("Resultado: %.2f - %.2f = %.2f\n", a, b, resultado);
                break;
                
            case 3:  // Multiplicación
                printf("Ingrese a: ");
                scanf("%lf", &a);
                printf("Ingrese b: ");
                scanf("%lf", &b);
                resultado = a * b;
                printf("Resultado: %.2f x %.2f = %.2f\n", a, b, resultado);
                break;
                
            case 4:  // División y módulo
                printf("Ingrese el numero: ");
                scanf("%lf", &a);
                printf("Ingrese el denominador: ");
                scanf("%lf", &b);
                if (b == 0) {
                    printf("Error: Division por cero.\n");
                    es_valido = 0;
                } else {
                    double division = a / b;
                    int a_int = (int)a;
                    int b_int = (int)b;
                    int modulo = a_int % b_int;
                    printf("Resultado: %.2f / %.2f = %.2f\n", a, b, division);
                    printf("Modulo: %d %% %d = %d\n", a_int, b_int, modulo);
                    resultado = division;
                }
                break;
                
            case 5:  // Potencia entera
                {
                    int exp;
                    printf("Ingrese la base: ");
                    scanf("%lf", &a);
                    printf("Ingrese el exponente: ");
                    scanf("%d", &exp);
                    if (exp < 0) {
                        printf("Error: Exponente negativo no soportado.\n");
                        es_valido = 0;
                    } else {
                        double potencia = 1.0;
                        for (i = 0; i < exp; i++) {
                            potencia *= a;
                            if (potencia > 1e308) {
                                printf("Error: Overflow en potencia.\n");
                                es_valido = 0;
                                break;
                            }
                        }
                        if (es_valido) {
                            resultado = potencia;
                            printf("Resultado: %.2f ^ %d = %.2f\n", a, exp, resultado);
                        }
                    }
                }
                break;
                
            case 6:  // Factorial
                {
                    int n;
                    printf("Ingrese n: ");
                    scanf("%d", &n);
                    if (n < 0) {
                        printf("Error: Factorial de numero negativo no definido.\n");
                        es_valido = 0;
                    } else if (n > 20) {
                        printf("Error: Factorial de %d produce overflow (max 20).\n", n);
                        es_valido = 0;
                    } else {
                        long long fact = 1;
                        for (i = 2; i <= n; i++) {
                            fact *= i;
                        }
                        resultado = (double)fact;
                        printf("Resultado: %d! = %lld\n", n, fact);
                    }
                }
                break;
                
            case 7:  // ¿Es primo?
                {
                    int n;
                    printf("Ingrese n: ");
                    scanf("%d", &n);
                    if (n <= 1) {
                        printf("%d no es primo\n", n);
                        resultado = 0;
                    } else {
                        int es_primo = 1;
                        for (i = 2; i * i <= n; i++) {
                            if (n % i == 0) {
                                printf("%d no es primo (divisible por %d)\n", n, i);
                                es_primo = 0;
                                break;
                            }
                        }
                        if (es_primo) {
                            printf("%d ES primo\n", n);
                            resultado = 1;
                        } else {
                            resultado = 0;
                        }
                    }
                }
                break;
                
            case 8:  // MCD (Euclides iterativo)
                {
                    int a_int, b_int;
                    printf("Ingrese a: ");
                    scanf("%d", &a_int);
                    printf("Ingrese b: ");
                    scanf("%d", &b_int);
                    
                    // Tomar valores absolutos
                    if (a_int < 0) a_int = -a_int;
                    if (b_int < 0) b_int = -b_int;
                    
                    if (a_int == 0 && b_int == 0) {
                        printf("Error: MCD(0,0) no definido.\n");
                        es_valido = 0;
                    } else {
                        int temp;
                        while (b_int != 0) {
                            temp = b_int;
                            b_int = a_int % b_int;
                            a_int = temp;
                        }
                        resultado = a_int;
                        printf("Resultado: MCD = %d\n", a_int);
                    }
                }
                break;
        }
        
        // Limpiar el buffer del teclado después de scanf
        while (getchar() != '\n');
        
        // Si la operación fue válida, actualizar historial y contadores
        if (es_valido) {
            ultimo_resultado = resultado;
            hay_resultado = 1;
            
            // Actualizar historial circular (últimas 20)
            historial[total_ops % 20] = opcion;
            total_ops++;
            
            // Actualizar contador
            contadores[opcion]++;
        }
    }
    
    return 0;
}
