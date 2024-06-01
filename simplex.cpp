#include <iostream> // libreria para imprimir en consola

using namespace std;
// JORGE GUILLERMO OLARTE QUISPE
const int numRestricciones = 2; // Número de restricciones (si se usa otro valor asegure cambiar la tabla)
const int numVariables = 2; // Número de variables(si se usa otro valor asegure cambiar la tabla)

// Función para imprimir el tableau
void imprimirTabla(double tabla[numRestricciones + 1][numVariables + numRestricciones + 1]) {
    // Iterar sobre cada fila de la tabla
    for (int i = 0; i < numRestricciones + 1; ++i) {
        // Iterar sobre cada columna de la tabla
        for (int j = 0; j < numVariables + numRestricciones + 1; ++j) {
            // Imprimir el valor de la tabla con un ancho fijo
            cout << " " << tabla[i][j] << " ";
        }
        // Agregar una nueva línea después de imprimir cada fila
        cout << endl;
    }
    // Imprimir una línea en blanco después de imprimir la tabla completa
    cout << endl;
}

// Función para realizar el algoritmo simplex
void simplex(double tabla[numRestricciones + 1][numVariables + numRestricciones + 1]) {
    int filas = numRestricciones + 1; // Número de filas en la tabla
    int columnas = numVariables + numRestricciones + 1; // Número de columnas en la tabla

    // Iniciar el bucle principal del algoritmo simplex
    while (true) {
        // Encontrar la columna pivote (la más negativa en la fila objetivo)
        int colPivote = -1; // Índice de la columna pivote
        double minVal = 0; // Valor mínimo en la fila objetivo

        // Iterar sobre cada columna en la fila objetivo
        for (int j = 0; j < columnas - 1; ++j) {
            // Buscar la columna con el valor más negativo en la fila objetivo
            if (tabla[filas - 1][j] < minVal) {
                minVal = tabla[filas - 1][j]; // Actualizar el valor mínimo
                colPivote = j; // Actualizar el índice de la columna pivote
            }
        }

        // Verificar si todas las entradas en la fila objetivo son no negativas
        if (colPivote == -1) break; // Salir del bucle si todas son no negativas

        // Encontrar la fila pivote usando la regla de razón mínima
        int filPivote = -1; // Índice de la fila pivote
        double minRazon = 1.0e30; // Valor inicial para la razón mínima (casi infinito)

        // Iterar sobre cada fila, excepto la última (la fila objetivo)
        for (int i = 0; i < filas - 1; ++i) {
            // Verificar si el elemento en la columna pivote es positivo
            if (tabla[i][colPivote] > 0) {
                // Calcular la razón entre el valor en la columna de resultados y el valor en la columna pivote
                double razon = tabla[i][columnas - 1] / tabla[i][colPivote];
                // Actualizar la fila pivote si la razón es menor que la mínima encontrada hasta ahora
                if (razon < minRazon) {
                    minRazon = razon; // Actualizar la razón mínima
                    filPivote = i; // Actualizar el índice de la fila pivote
                }
            }
        }

        // Verificar si no se puede encontrar una fila pivote válida
        if (filPivote == -1) {
            // Imprimir un mensaje de error y salir de la función
            cout << "Problema sin solución acotada" << endl;
            return;
        }

        // Hacer que el pivote sea igual a 1 en la fila pivote
        double pivote = tabla[filPivote][colPivote]; // Valor del pivote

        // Iterar sobre cada elemento en la fila pivote y dividirlo por el pivote
        for (int j = 0; j < columnas; ++j) {
            tabla[filPivote][j] /= pivote;
        }

        // Hacer ceros en la columna pivote en todas las filas excepto la fila pivote
        for (int i = 0; i < filas; ++i) {
            // Saltar la fila pivote
            if (i != filPivote) {
                // Calcular el factor de multiplicación
                double factor = tabla[i][colPivote];
                // Iterar sobre cada elemento en la fila y restar el producto del factor y el elemento correspondiente en la fila pivote
                for  (int j = 0; j < columnas; ++j) {
                    tabla[i][j] -= factor * tabla[filPivote][j];
                }
            }
        }

        // Imprimir la tabla en cada iteración
        imprimirTabla(tabla);
    }

    // Imprimir la solución óptima después de salir del bucle principal
    cout << "Solución Optima: " << tabla[filas - 1][columnas - 1] << endl;
}

// Función principal del programa
int main() {
    // Inicializar la tabla con valores dados en el problema
    double tabla[numRestricciones + 1][numVariables + numRestricciones + 1] =
    {
        {2, 1, 1, 0, 6}, // L1
        {1, -1, 0, 1, 0}, // L2
        {-5, -1, 0, 0, 0} // L0

    };

//  Ejemplo de Cuaderno (RESPUESTA: 8) (Cambiar variables de VARIABLES y RESTRICCIONES a 2, 3  respectivamente)
//    {
//        {-2, 3, 1, 0, 0, 6}, //L1
//        {1, 2, 0, 1, 0, 8}, // L2
//        {1, 1, 0, 0, 1, 6}, // L3
//        {-1, -2, 0, 0, 0, 0} // L0
//    };


//  EJEMPLO de examen (RESPUESTA: 12); (Cambiar variables de VARIABLES y RESTRICCIONES a 2, 2 respectivamente)

//        {2, 1, 1, 0, 6}, // L1
//        {1, -1, 0, 1, 0}, // L2
//        {-5, -1, 0, 0, 0} // L0
//  EJEMPLO de aleatorio (RESPUESTA: 32); (Cambiar variables de VARIABLES y RESTRICCIONES a 3, 3 respectivamente)

//        {1, 2, 3, 1, 0, 0, 30}, // L1 ( ejemplo x4)
//        {2, 2, 5, 0, 1, 0, 24}, // L2 ( ejemplo x5)
//        {4, 1, 2, 0, 0, 1, 36}, // L3 ( ejemplo x6)
//        {-3, -2, -1, 0, 0, 0, 0} // L0 ( max )

    // Imprimir la tabla inicial antes de ejecutar el algoritmo simplex
    cout << "Tabla Inicial: " << endl;
    imprimirTabla(tabla);

    // Ejecutar el algoritmo simplex para resolver el problema de programación lineal
    simplex(tabla);

    // Devolver un valor entero como indicador de que el programa terminó correctamente
    return 0;
}

