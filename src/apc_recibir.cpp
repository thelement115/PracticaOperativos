#include "apc.h"

int APC_Recibir(ConexionSeccion_t* conexion, int *valor) {
  sem_wait(conexion->vacios);
  sem_wait(conexion->mutex);
  *valor = conexion->buffer[*conexion->sale];
  *conexion->sale = (*conexion->sale+1)%*conexion->tamano;
  sem_post(conexion->mutex);
  sem_post(conexion->llenos);
  return 0;
}


