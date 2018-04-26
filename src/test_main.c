#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __MIPS__
extern int trasponer(unsigned int filas, unsigned int columnas, const long long *entrada,
                     long long *salida);
#else
#include "matrix.h"
#endif

void assert_eq(size_t size, const long long *obtained, const long long *expected) {
  for (size_t i = 0; i < size; i++) {
    if (obtained[i] != expected[i]) {
      printf("  [ERROR]\n");
      exit(1);
    }
  }

  printf("  [OK]\n");
}

void test(int rows, int cols, const long long *in, const long long *expected) {
  long long obtained[rows * cols];
  trasponer(rows, cols, in, obtained);

  assert_eq(rows * cols, obtained, expected);
}

int main(int argc, const char *argv[]) {
  /* 3x3 */
  {
    printf("Matriz de 3x3\n");
    long long in[] = {0, 1, 2,  //
                      3, 4, 5,  //
                      6, 7, 8};
    const long long expected[] = {0, 3, 6,  //
                                  1, 4, 7,  //
                                  2, 5, 8};
    int rows = 3;
    int cols = 3;

    test(rows, cols, in, expected);
  }

  /* 3x5 */
  {
    printf("Matriz de 3x5\n");
    long long in[] = {0,  1,  2,  3,  4,  //
                      5,  6,  7,  8,  9,  //
                      11, 12, 13, 14, 15};
    const long long expected[] = {0, 5, 11,  //
                                  1, 6, 12,  //
                                  2, 7, 13,  //
                                  3, 8, 14,  //
                                  4, 9, 15};
    int rows = 3;
    int cols = 5;

    test(rows, cols, in, expected);
  }

  /* 1x1 */
  {
    printf("Matriz de 1x1\n");
    long long in[] = {10};
    const long long expected[] = {10};
    int rows = 1;
    int cols = 1;

    test(rows, cols, in, expected);
  }

  /* 1x5 */
  {
    printf("Matriz de 1x5\n");
    long long in[] = {4, 3, 2, 1, 0};
    const long long expected[] = {4, 3, 2, 1, 0};
    int rows = 1;
    int cols = 1;

    test(rows, cols, in, expected);
  }

  /* 5x1 */
  {
    printf("Matriz de 5x1\n");
    long long in[] = {4, 3, 2, 1, 0};
    const long long expected[] = {4, 3, 2, 1, 0};
    int rows = 5;
    int cols = 1;

    test(rows, cols, in, expected);
  }

  return 0;
}
