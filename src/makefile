GCC_FLAGS = -std=c99

c: main.c matrix.c
	gcc $(GCC_FLAGS) main.c matrix.c -o tp

assembly: main.c matrix.S
	gcc $(GCC_FLAGS) main.c matrix.S -o tp_assembly -D__MIPS__

test_c: test_main.c matrix.c
	gcc $(GCC_FLAGS) test_main.c matrix.c -o test_c

test_assembly: test_main.c matrix.S
	gcc $(GCC_FLAGS) test_main.c matrix.S -o test_assembly -D__MIPS__

