#include <ctype.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "matrix.h"

struct args {

  /* Path del archivo con los datos de entrada */
  const char* path_entrada;

  /* Path salida */
  const char* path_salida;
  
  /* Boolean indica si se usa stdout */
  bool usa_std_out;
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

static void _arg_parse(struct args* args,int argc, const char **argv) {
    
  int ch = -1;
  args->usa_std_out = true;

  while ((ch = getopt_long(argc, (char **)argv, "hVo:", _long_opts, NULL)) != -1) {
    switch (ch) {
      case 'h':
        _print_help(argv[0]);
        exit(0);
        break;

      case 'V':
        _print_version(argv[0]);
        exit(0);
        break;
        
      case 'o':
        args->usa_std_out = false;
        args->path_salida = argv[optind - 1];
        break;
        
      /* this is returned when a required argument was not provided */
      case '?':
        exit(1);
        break;
      
    }
  }
  
  if(optind < argc){
    args->path_entrada = argv[optind]; 
    optind++;       
    }else{ 
       fprintf( stderr, "No file specified\n"); 
       exit(1); 
    }
}

void abrir_archivos(struct args args, FILE** archivo_entrada, FILE** archivo_salida){
    *archivo_entrada = fopen(args.path_entrada, "r");
    if (*archivo_entrada == 0) {
       perror("Input file error");
    }
    
    if(args.usa_std_out)
        *archivo_salida = stdout;
    else{
        *archivo_salida = fopen(args.path_salida, "w");
        if (*archivo_salida == 0) {
            perror("Output file error");
        }
    }
    
    //Si alguno de los dos fallo cancelo lo hecho y salgo
    if(*archivo_entrada == 0 || *archivo_salida == 0){
        
        if(*archivo_entrada != 0){
            fclose(*archivo_entrada);
        }
        
        if(*archivo_salida != 0){
            fclose(*archivo_salida);
            remove(args.path_salida);
        }
        
        exit(1);
    }
}

int main(int argc, const char *argv[]){
    struct args args;
    FILE* archivo_entrada;
    FILE* archivo_salida;
    unsigned int cantidad_de_filas;
    unsigned int cantidad_de_columnas;
    unsigned int cantidad_de_filas_traspuesta;
    unsigned int cantidad_de_columnas_traspuesta;
    long long int* matriz_entrada;
    long long int* matriz_salida;
    int i = 0;
    char* direccion_caracter_no_numerico = NULL;
    char string_cargado[50];
    long long int numero_cargado;
    _arg_parse(&args,argc, argv);
    
    abrir_archivos(args, &archivo_entrada, &archivo_salida);

    fscanf(archivo_entrada,"%u %u\n", &cantidad_de_filas, &cantidad_de_columnas );
    matriz_entrada = malloc(sizeof(long long int) * cantidad_de_filas * cantidad_de_columnas);
    matriz_salida = malloc(sizeof(long long int) * cantidad_de_filas * cantidad_de_columnas);
    
    //Cargo la matriz de entrada
    while(fscanf(archivo_entrada, "%s ", string_cargado) != EOF){
        
        numero_cargado = strtoll(string_cargado, &direccion_caracter_no_numerico, 0); //Esta en base 10;
        
        if(*direccion_caracter_no_numerico != '\0'){
            fprintf( stderr, "Input file doesn't have a valid format\n"); 
            exit(1);
        }
        
        matriz_entrada[i] = numero_cargado;
        i++;
        
    }
    
    trasponer(cantidad_de_filas, cantidad_de_columnas, matriz_entrada, matriz_salida);
    cantidad_de_columnas_traspuesta = cantidad_de_filas;
    cantidad_de_filas_traspuesta = cantidad_de_columnas;
    
    fprintf(archivo_salida, "%u %u\n", cantidad_de_filas_traspuesta, cantidad_de_columnas_traspuesta );
    for (unsigned i = 0; i < cantidad_de_filas_traspuesta; i++) {
        for (unsigned j = 0; j < cantidad_de_columnas_traspuesta; j++) {
            fprintf(archivo_salida, "%lld ",matriz_salida[i * cantidad_de_columnas_traspuesta + j]);
        } 
        fputc('\n', archivo_salida);
    }
    
    free(matriz_entrada);
    free(matriz_salida);
    
}
