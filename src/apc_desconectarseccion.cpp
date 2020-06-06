#include "apc.h"

int APC_DesconectarSeccion(ConexionSeccion_t* conexion) {
  if(conexion == NULL){
    errno = APC_ERROR_ARGUMENTO;
    return -1;
  }

  int sem1 = sem_destroy(conexion->vacios);
  int sem2 = sem_destroy(conexion->llenos);
  int sem3 = sem_destroy(conexion->mutex);
  if (sem1 <0 || sem2 < 0 || sem3 <0){
    errno = APC_ERROR_NOCONEXION;
    return -1;
  }
  return 0;
}


