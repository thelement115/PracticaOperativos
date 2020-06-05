#include "apc.h"

int APC_ActivarSeccion(const char* nombreArea, const char *nombreSeccion, size_t tamano) {
  int fd = shm_open(nombreArea, O_RDWR, 0660);
  if (fd < 0) {
    errno = APC_ERROR_NOEXISTE;
    return APC_FAIL;
  }

  void *dir;

  if ((dir = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED,
		  fd, 0)) == MAP_FAILED) {
    errno = APC_ERROR_DESCONOCIDO;
    return APC_FAIL;
  }

  struct area *pArea = (struct area *) dir;

  struct admin pAdmin = pArea->admin;

  int total = pAdmin.tamano;

  if(tamano > total){
    errno = APC_ERROR_NOMEMORIA;
    return APC_FAIL;
  }

  for(int i =0; i< 10; i++){
    struct seccion_T seccion = pArea->secciones[i];
    if(seccion.active){
      int aux = seccion.limite-seccion.base;
      total = total-aux;
    }
  }

  if(total< tamano){
    errno = APC_ERROR_NOMEMORIA;
    return APC_FAIL;
  }
}


