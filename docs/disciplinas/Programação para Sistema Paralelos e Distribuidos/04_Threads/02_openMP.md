# Biblioteca OpenMP


O O OpenMP é um dos frameworks é um dos modelos de programação paralelas mais utilizadas hoje em dia. Ele é utilizado importando a biblioteca `#include <omp.h>`


## 1. Como compilar



1. `gcc -fopenmp paralelo.c`
    - Comando para compilar um arquivo paralelo.c  
    

2. `export OMP_NUM_THREADS=X`

    - Comando para controlar o número de threads em paralelo

3. `./a.out`
    
    - Comando para gerar o programa compilado

## 2. Funções principais

1. `#include <omp.h>` 
    - Import da biblioteca

2. `int omp_get_thread_num();` 
    - Retorna o número da thread.

3. `void omp_set_num_threads(int num_threads);` 
    - Indica quantas threads vao ser ser executadas.

4. `void omp_get_num_threads();` 
    - Indica o número de threads que estão sendo executadas.

5. `#pragma opm parallel private(x) {}`
    - Indica região a ser paralelizada

6. `#pragma omp single`
    - O código precisamente abaixo vai ser rodado somente pela thread principal.

## 3. Exemplos Iniciais

### 1. Hello World com todas threads

```C
#include <stdio.h>
#include <omp.h>

int main (){
    int nthreads;
    int id;

    #pragma omp parallel private (id, nthreads)
    {
        id = omp_get_thread_num();

        nthreads = omp_get_num_threads();

        printf("%d of %d - hello world!\n", id, nthreads);
    }

    return 0;
}

/// bash
$ gcc -fopenmp teste.c
$ ./a.out
1 of 4 - hello world!
2 of 4 - hello world!
0 of 4 - hello world!
3 of 4 - hello world!
```

### 1.2 Hello World somente pela thread principal

```C
#include <stdio.h>
#include <omp.h>

int main (){
    int nthreads;
    int id;

    #pragma omp parallel private(id, nthreads)
    {
        id = omp_get_thread_num();
        nthreads = omp_get_num_threads();

        #pragma omp single
        printf("%d of %d, Sou a principal\n", id, nthreads);
    }
    return 0;
}

/// bash
$ gcc -fopenmp teste.c
$ ./a.out
1 of 4, Sou a principal
$ ./a.out
0 of 4, Sou a principal
$ ./a.out
2 of 4, Sou a principal
```

## 4. Laços