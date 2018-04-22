#include <mips/regdef.h>

# trasponer(unsigned int, unsigned int, long long const*, long long*):
.global trasponer
trasponer:
    subu    sp, sp, 8       # muevo el stack pointer
    sw      $fp, 4(sp)
    sw      gp, 0(sp)

    # parametros de entrada
    sw		a0, 8(sp)		# filas
    sw		a1, 12(sp)		# columnas
    sw		a2, 16(sp)		# entrada
    sw		a3, 20(sp)		# salida

    # inicializa las variables locales
    li		t0, 0		    # $t0 = 0 (contador filas)
    li		t2, 0		    # $t2 = 0 (condicion de corte loop filas)

loop_rows:
    slt     t2, t0, a0      # if( a0 < t0 )
    beq  	t2, zero, end   #   goto end;

    # inicializa el loop de columnas
    li		t1, 0		    # $t1 = 0 (contador columnas)
    li		t3, 0		    # $t3 = 0 (condicion de corte loop columnas)

loop_cols:
    slt     t3, t1, a1      # if( a1 < t1 )
    beq 	t3, zero, end_cols 	#   goto end_cols;

    # copia el valor de la matriz de entrada a la de salida
    mulou   t4, t1, a0      # t4 = t1 * a0 + t0 (indice de salida)
    addu    t4, t0
    sll     t4, t4, 3       # multiplica por 8
    addu    t4, a3

    mulou   t5, t0, a1      # t5 = t0 * a1 + t1 (indice de entrada)
    addu    t5, t1
    sll     t5, t5, 3
    addu    t5, a2

    lw      t6, 0(t5)       # carga el valor del indice
    lw      t7, 4(t5)       # en 2 partes (por ser un long long)

    sw		t6, 0(t4)   	# copia las 2 words
    sw		t7, 4(t4)   	# copia las 2 words

    # incrementa el contador de columas
    addi	t1, t1, 1		# t1 = t1 + 1
    j		loop_cols		# jump a loop_cols

end_cols:
    # incrementa el contador de filas
    addi	t0, t0, 1		# t0 = t0 + 1
    j		loop_rows   	# jump a loop_cols

end:
    # restaura los resgitros
    lw		gp, 0(sp)
    lw		$fp, 4(sp)
    li		v0, 0		    # v0 = 0
    jr		ra				# retorna
