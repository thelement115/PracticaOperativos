#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include "apc.h"

int APC_Enviar(ConexionSeccion_t* conexion, int valor) {
  sem_wait(conexion->vacios);
  sem_wait(conexion->mutex);
  conexion->buffer[*conexion->entra] = valor;
  *conexion->entra = (*conexion->entra+1)%*conexion->tamano;
  sem_post(conexion->mutex);
  sem_post(conexion->llenos);
  return 0;
}


