#pragma once

#define N_BUFFER 10
const int MAX_NOMBRE = 64;

struct elemento {
  int elemento;
};

struct Buffer {
  int entra;
  int sale;
  int cantidad;
  int tamano;
  struct elemento buffer[N_BUFFER];
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

