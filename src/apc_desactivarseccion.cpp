#include "apc.h"

int APC_DesactivarSeccion(const char*nombreArea, const char *nombreSeccion) {
  size_t len = strlen(nombreArea);
  size_t len2 = strlen(nombreSeccion);
  
  if(nombreArea==NULL || nombreSeccion == NULL || len > MAX_NOMBRE ||len2>MAX_NOMBRE){
    errno = APC_ERROR_ARGUMENTO;
    return APC_FAIL;
  }
  
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

  for(int i =0; i< 10; i++){
    struct seccion_T &seccion = pArea->secciones[i];
    if(seccion.active){
      if (strcmp(nombreSeccion,seccion.nombre) == 0){
        seccion.active = false;
        return EXIT_SUCCESS;
      }
    }
  }

  errno = APC_ERROR_NOSECCION;
  return APC_FAIL;
}


