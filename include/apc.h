#pragma once
#include <fcntl.h>  
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

const int MAX_NOMBRE = 64;

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
    int buffer[10000];
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
