# Obligatorio 01 — Calculadora de consola

**UTEC · UTU · Facultad de Ingeniería — UdelaR**  
Trabajo individual — Bloque 1

---

## Cómo compilar y ejecutar

Se necesita un compilador GCC. Desde la carpeta del proyecto:

```bash
# Programa principal
gcc -Wall -Wextra -o calc calc.c
./calc

# Satélite A — Estadísticas
gcc -Wall -Wextra -o stats stats.c
./stats

# Satélite B — Figuras huecas
gcc -Wall -Wextra -o patrones patrones.c
./patrones
```

Los tres archivos compilan sin warnings con `-Wall -Wextra`.

---

## Descripción de cada programa

### `calc.c` — Calculadora con memoria

Menú interactivo con 8 operaciones numéricas (suma, resta, multiplicación, división+módulo, potencia entera, factorial, primo, MCD) más 4 comandos de memoria (M+, M-, MR, MC) y el comando H para ver el historial.

- El historial guarda las últimas 20 operaciones en un arreglo circular. Cuando `total_ops` supera 20, el índice `total_ops % 20` sobrescribe la entrada más vieja.
- `contadores[9]` acumula cuántas veces se usó cada operación (índices 1 a 8).
- Al salir con `0` se muestra la operación más usada.
- La entrada de texto se lee con `fgets` para poder distinguir comandos de letra (M+, H) de opciones numéricas, evitando que `scanf` deje basura en el buffer cuando el usuario escribe letras.

### `stats.c` — Estadísticas con orden

Lee hasta 100 enteros (0 termina la carga), los ordena con bubble sort y calcula: cantidad, suma, promedio, mínimo, máximo, mediana, moda y un histograma ASCII escalado.

- El bubble sort ordena el arreglo de menor a mayor; eso permite obtener mínimo y máximo directo de los extremos y la mediana del centro sin recorridas extra.
- Para la moda y el histograma se construyen dos arreglos paralelos (`unicos[]` y `freqs[]`) contando rachas consecutivas sobre el arreglo ya ordenado — una sola pasada alcanza para todo.
- En caso de empate en la moda, gana el valor menor, lo cual sale naturalmente porque se recorre de izquierda a derecha con `>` (sin `>=`).
- "Duplicados" cuenta cuántos valores distintos aparecen más de una vez.
- El histograma escala las barras de `#` para que la mayor frecuencia ocupe 40 caracteres y el resto sea proporcional.

### `patrones.c` — Figuras huecas

Pide una altura `n` (entre 3 y 20) y dibuja una pirámide hueca y un rombo hueco, construyendo primero cada figura en una matriz de `char` y luego imprimiéndola línea por línea.

- **Pirámide**: matriz `pir[n][2n-1]` inicializada en espacios. La cima es un solo `*`; la base es una fila entera de `*`; las filas intermedias llevan solo los dos extremos.
- **Rombo**: matriz `rombo[2n-1][2n-1]`. Se calcula la distancia `dist` de cada fila a la fila central para determinar las columnas izquierda y derecha. Cuando `izq == der` (vértice superior o inferior) se pone un solo `*`; de lo contrario solo los dos extremos.

---

## Decisiones de diseño

- **Sin funciones propias**: todo el código vive dentro de `main`, como exige el bloque 1.
- **Sin punteros ni variables globales**: se usan únicamente arreglos locales declarados con tamaño fijo.
- **Lectura de entrada en `calc.c`**: se usa `fgets` + `sscanf` para el menú principal, lo que permite leer comandos como `M+` o `H` sin que el programa quede bloqueado ni deje caracteres sueltos en el buffer. Dentro de cada operación se usa `scanf` seguido de un vaciado de buffer con `while (getchar() != '\n')`.
- **Overflow en factorial y potencia**: factorial está limitado a n ≤ 20 (20! cabe en `long long`); la potencia acumula el resultado en un `double` y corta si supera 1e308.
- **MCD con negativos**: se toman valores absolutos antes del algoritmo de Euclides. MCD(0,0) se reporta como error.
- **Histograma escalado en stats.c**: escalar al máximo de 40 columnas hace que el histograma sea legible independientemente de las frecuencias reales.

---

## Qué me costó más

- El manejo de entrada mixta en `calc.c` (números y comandos de letra en el mismo prompt) fue lo más delicado. Usar `fgets` resolvió el problema pero requirió limpiar bien el buffer antes de las lecturas con `scanf` dentro de cada operación.
- La lógica del rombo hueco en `patrones.c` tardó un poco en quedar clara: calcular `dist` como distancia absoluta a la fila central simplificó bastante el código comparado con tratar la mitad superior e inferior por separado.

---

## Uso de inteligencia artificial

Se utilizó **Claude (Anthropic)** como asistente durante el desarrollo del obligatorio, específicamente para:

- Implementar algunas funciones de `stats.c` y `patrones.c` a partir de la especificaciónes.
- Verificar que el código compilara sin warnings con `-Wall -Wextra`.
- Escribir la documentacion de forma prolija y alineada al código

El código fue revisado y comprendido en su totalidad antes de incluirlo en la entrega. Se entiende la lógica de cada bloque: el bubble sort, el índice circular del historial, el cálculo de distancia para el rombo y el escalado proporcional del histograma.

---

## Estructura del proyecto

```
obligatorio1_<apellido>/
├── calc.c        — Programa principal: calculadora con memoria
├── stats.c       — Satélite A: estadísticas con orden e histograma
├── patrones.c    — Satélite B: pirámide y rombo huecos
└── README.md     — Este archivo
```