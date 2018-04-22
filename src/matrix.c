#include "matrix.h"

/**
 * @brief Transpone una matriz almacenada en un array de long long.
 *
 * @param filas Cantidad de filas en la matriz.
 * @param columnas Cantidad de columnas en la matriz.
 * @param entrada Puntero a la matriz de entrada.
 * @param salida Puntero a la matriz de salida.
 * @return 0 siempre.
 */
int trasponer(unsigned int filas, unsigned int columnas, const long long *entrada,
              long long *salida) {
  for (unsigned i = 0; i < filas; i++) {
    for (unsigned j = 0; j < columnas; j++) {
      salida[j * filas + i] = entrada[i * columnas + j];
    }
  }

  return 0;
}
