#include <ctype.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct args {

  /* Path del archivo con los datos de entrada */
  const char* pathEntrada;

  /* Boolean ndica si se usa stdin */
  const char* pathSalida;
};


/** Estructura que uitliza getopt_log para parsear los argumentos de linea de
 * comandos. */
static const struct option _long_opts[] = {
    {.name = "help", .has_arg = no_argument, .flag = NULL, .val = 'h'},
    {.name = "version", .has_arg = no_argument, .flag = NULL, .val = 'V'},
    {.name = "output", .has_arg = required_argument, .flag = NULL, .val = 'o'},
    {0},
};

/**
 * @brief Imprime un mensaje de ayuda y termina el programa.
 *
 * @param bin_name argv[0].
 */
static void _print_help(const char *bin_name) {
  printf("Usage:\n");
  printf("   traspuesta -h\n");
  printf("   traspuesta -V\n");
  printf("   traspuesta [options] filename\n");
  printf("Options:\n");
  printf("  -h, --help        Prints usage information.\n");
  printf("  -V, --version     Prints version information.\n");
  printf("  -o, --output      Path to output file.\n");
}

/**
 * @brief Imprime la versión del programa y termina.
 *
 * @param bin_name argv[0].
 */
static void _print_version(const char *bin_name) {
  printf("%s, versión 1.00\n", bin_name);
}

static void _arg_parse(int argc, const char **argv) {
    
  int ch = -1;

  while ((ch = getopt_long(argc, (char **)argv, "hVbcwli:", _long_opts, NULL)) != -1) {
    switch (ch) {
      case 'h':
        _print_help(argv[0]);
        exit(0);
        break;

      case 'V':
        _print_version(argv[0]);
        exit(0);
        break;
        
      /* this is returned when a required argument was not provided */
      case ':':
      case '?':
        exit(1);
    }
  }
}


int main(int argc, const char *argv[]){
    _arg_parse(argc, argv);
}
