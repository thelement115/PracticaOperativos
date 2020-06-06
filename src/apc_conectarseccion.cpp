#include "apc.h"

ConexionSeccion_t* APC_ConectarSeccion(const char*nombreArea, const char *nombreSeccion) {
  size_t len = strlen(nombreArea);
  size_t len2 = strlen(nombreSeccion);
  
  if(nombreArea==NULL || nombreSeccion == NULL || len > MAX_NOMBRE ||len2>MAX_NOMBRE){
    errno = APC_ERROR_ARGUMENTO;
    return NULL;
  }
  
  int fd = shm_open(nombreArea, O_RDWR, 0660);
  if (fd < 0) {
    errno = APC_ERROR_NOEXISTE;
    return NULL;
  }

  void *dir;

  if ((dir = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED,
		  fd, 0)) == MAP_FAILED) {
    errno = APC_ERROR_DESCONOCIDO;
    return NULL;
  }

  struct area *pArea = (struct area *) dir;
  struct seccion_T *pSeccion = NULL;

  for(int i =0; i< 10; i++){
    struct seccion_T &seccion = pArea->secciones[i];
    if(seccion.active){
      if (strcmp(nombreSeccion,seccion.nombre) == 0){
        *pSeccion = seccion;
      }
    }
  }

  if(pSeccion == NULL){
    errno = APC_ERROR_NOSECCION;
    return NULL;
  }

  struct ConexionSeccion* ConexionSeccion_t;

  int* tamano =(int*)pSeccion->limite - pSeccion->base;

  sem_t *vacios = sem_open(pSeccion->semVacios, O_CREAT | O_EXCL, 0660, tamano);
  sem_t *llenos = sem_open(pSeccion->semLlenos, O_CREAT | O_EXCL, 0660, 0);
  sem_t *mutex  = sem_open(pSeccion->semMutex, O_CREAT | O_EXCL, 0660, 1);

  ConexionSeccion_t->buffer = (int*)(dir + sizeof(struct area));
  ConexionSeccion_t->entra = (int*) pSeccion->base;
  ConexionSeccion_t->sale = (int*) pSeccion->base;
  ConexionSeccion_t->tamano = tamano;
  ConexionSeccion_t->vacios = vacios;
  ConexionSeccion_t->llenos = llenos;
  ConexionSeccion_t->mutex = mutex;

  return ConexionSeccion_t;
}


