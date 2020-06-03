#pragma once

#include <semaphore.h>
#define N_BUFFER 10
const int MAX_NOMBRE = 64;

struct elemento {
  int elemento;
};


struct ConexionSeccion_t {
  int* buffer;
  int tamano;
  int  entra;
  int  sale;
  sem_t* vacios;
  sem_t* llenos;
  sem_t* mutex;
};

struct Section_t{
  char nombre[MAX_NOMBRE];
  bool activa;
  unsigned long base;
  unsigned long limite;
  char semLlenos[MAX_NOMBRE];
  char semVacios[MAX_NOMBRE];
  char semMutex[MAX_NOMBRE];
};

