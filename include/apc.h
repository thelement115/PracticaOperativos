#pragma once
#include <fcntl.h>  
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdint>

const int MIN_TAMANO = 1000;
const int MAX_TAMANO = 1000000;
const int MAX_NOMBRE = 64;
const int APC_ERROR_EXISTE = 1;
const int APC_ERROR_ARGUMENTO = 2;
const int APC_ERROR_DESCONOCIDO = 3;
const int APC_ERROR_NOEXISTE = 4;
const int APC_ERROR_LLENO = 5;
const int APC_ERROR_NOMEMORIA = 6;
const int APC_ERROR_NOSECCION = 7;
const int APC_ERROR_NOCONEXION = 8;
const int APC_FAIL = -1;


typedef struct ConexionSeccion {
  int* buffer;
  int *tamano;
  int  *entra;
  int  *sale;
  sem_t* vacios;
  sem_t* llenos;
  sem_t* mutex;
} ConexionSeccion_t;

struct seccion_T{
  char nombre[MAX_NOMBRE];
  bool active;
  unsigned long base;
  unsigned long limite;
  char semLlenos[MAX_NOMBRE];
  char semVacios[MAX_NOMBRE];
  char semMutex[MAX_NOMBRE];
};

struct admin{
    int entra;
    int tamano;
    int sale;
};

struct area{
  char nombre[MAX_NOMBRE];
  struct admin admin;
  struct seccion_T secciones[10];
};

int APC_Init(const char* nombre, size_t tamano);
int APC_Terminar(const char *nombre);
int APC_ActivarSeccion(const char* nombreArea, const char *nombreSeccion, size_t tamano);
int APC_DesactivarSeccion(const char*nombreArea, const char *nombreSeccion);
ConexionSeccion_t* APC_ConectarSeccion(const char*nombreArea, const char *nombreSeccion);
int APC_DesconectarSeccion(ConexionSeccion_t* conexion);
int APC_Enviar(ConexionSeccion_t* conexion, int valor);
int APC_Recibir(ConexionSeccion_t* conexion, int *valor);
