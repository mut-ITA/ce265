#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void InitTabul(int*, int*, int);
void DumpTabul(int*, int, int, int, char*);
void UmaVida(int*, int*, int);
int Correto(int*, int);


int main(int argc, char *argv[]) {
  int i;
  int tam=6;
  int* tabulIn;
  int* tabulOut;
  int numProc, myId;
  char msg[9];
  
  // numero de processos, qual processo eu sou (substituir por MPI)

  if (myId == 0) printf("Execucao com %d processadores\n", numProc);

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProc);
  MPI_Comm_rank(MPI_COMM_WORLD, &myId); 

  if (numProc <= tam)
  {
    int tamLocal = tam/numProc;
    // Espalhar o resto
    if(myId < tam % numProc) {
      tamLocal++;
    }

    // Determinar a linha inicial do processo
    int linha = myId * (tam/numProc);
    // Somar os restos
    linha += min(myId, tam % numProc);

    // aloca e inicializa tabuleiros
    tabulIn  = (int *) malloc ((tamLocal+2)*(tam+2)*sizeof(int));
    tabulOut = (int *) malloc ((tamLocal+2)*(tam+2)*sizeof(int));
    InitTabul(tabulIn, tabulOut, tam, tamLocal, linha);
  }

  // // dump tabuleiro inicial

  // DumpTabul(tabulIn, tam, 1, tam, "Inicial");

  // for (i=0; i<2*(tam-3); i++) {

    // UmaVida(tabulIn, tabulOut, tam);
    // sprintf(msg,"Iter %3.3d\0", 2*i+1);
    // DumpTabul(tabulOut, tam, 1, tam, msg);

    // UmaVida(tabulOut, tabulIn, tam);
    // sprintf(msg,"Iter %3.3d\0", 2*i+2);
    // DumpTabul(tabulIn, tam, 1, tam, msg);
  // }

  // if (Correto(tabulIn, tam)) 
    // printf("**RESULTADO CORRETO**\n");
  // else
    // printf("**RESULTADO ERRADO**\n");

  // free(tabulIn);
  // free(tabulOut);

  MPI_Finalize();
  exit(0);    
}