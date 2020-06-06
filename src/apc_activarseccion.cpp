#include "apc.h"

int APC_ActivarSeccion(const char* nombreArea, const char *nombreSeccion, size_t tamano) {
  
  size_t len = strlen(nombreArea);
  size_t len2 = strlen(nombreSeccion);
  
  if(nombreArea==NULL || nombreSeccion == NULL || len > MAX_NOMBRE ||len2>MAX_NOMBRE || tamano <= 0){
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

  struct admin pAdmin = pArea->admin;

  int total = pAdmin.tamano;

  if(tamano > total){
    errno = APC_ERROR_NOMEMORIA;
    return APC_FAIL;
  }

  for(int i =0; i< 10; i++){
    struct seccion_T &seccion = pArea->secciones[i];
    if(seccion.active){
      if (strcmp(nombreSeccion,seccion.nombre) == 0){
        errno = APC_ERROR_ARGUMENTO;
        return APC_FAIL;
      }
      int aux = seccion.limite-seccion.base;
      total = total-aux;
    }
  }

  if(total< tamano){
    errno = APC_ERROR_NOMEMORIA;
    return APC_FAIL;
  }

  int pos = 0;
  int base = 0;
  int limite = 0;

  while(true){
    if(pos > 9){
      errno = APC_ERROR_LLENO;
      return APC_FAIL;
    }
    struct seccion_T &seccion = pArea->secciones[pos];
    if (!seccion.active){
      if(pos == 0){
        if(pArea->secciones[pos+1].base = 0){
          limite = tamano;
          break;
        }else{
          if(pArea->secciones[pos+1].base >= tamano){
            limite = tamano;
            break;
          }
        }
      }
      else if(pos == 9){
        if((pArea->admin.tamano - pArea->secciones[pos-1].limite) >= tamano+1){
          base = pArea->secciones[pos-1].limite+1;
          limite = base + tamano;
          break;
        }
      }else{
        if(pArea->secciones[pos+1].base = 0){
          base = pArea->secciones[pos-1].limite+1;
          limite = base + tamano;
          break;
        }
        if((pArea->secciones[pos+1].base - pArea->secciones[pos-1].limite) >= tamano+1){
          base = pArea->secciones[pos+1].limite+1;
          limite = base + tamano;
          break;
        }
      }
    }
    pos++;
  }

  const char *prefix0 = "vacio";
  const char *prefix1 = "llenos";
  const char *prefix2 = "mutex";

  char *vacio = (char*)malloc(strlen(nombreSeccion)+strlen(prefix0));
  char *llenos = (char*)malloc(strlen(nombreSeccion)+strlen(prefix1));
  char *mutex = (char*)malloc(strlen(nombreSeccion)+strlen(prefix2));
  strcpy(vacio,prefix0);
  strcat(vacio,nombreSeccion);
  strcpy(llenos,prefix1);
  strcat(llenos,nombreSeccion);
  strcpy(mutex,prefix0);
  strcat(mutex,nombreSeccion);

  struct seccion_T &seccion = pArea->secciones[pos];
  *(seccion.nombre) = *nombreSeccion;
  seccion.active = true;
  seccion.base = base;
  seccion.limite = limite;
  *(seccion.semVacios) = *vacio;
  *(seccion.semLlenos) = *llenos;
  *(seccion.semMutex) = *mutex;

  return EXIT_SUCCESS;
}


