#include "apc.h"

using namespace std;

int APC_Init(const char* nombre, size_t tamano) {

  if (nombre == NULL){
    errno = APC_ERROR_ARGUMENTO;
    return APC_FAIL;
  }

  size_t len = strlen(nombre);

  if (len > MAX_NOMBRE || tamano > MAX_TAMANO || tamano < MIN_TAMANO){
    errno = APC_ERROR_ARGUMENTO;
    return APC_FAIL;
  }

  int fd = shm_open(nombre, O_RDWR | O_CREAT | O_EXCL, 0660);

  if (fd < 0) {
    errno = APC_ERROR_EXISTE;
    return APC_FAIL;
  }

  if (ftruncate(fd, sizeof(struct area) + sizeof(int)* tamano) != 0) {
    errno = APC_ERROR_DESCONOCIDO;
    return APC_FAIL;
  }

  void *dir;

  if ((dir = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED,
		  fd, 0)) == MAP_FAILED) {
    errno = APC_ERROR_DESCONOCIDO;
    return APC_FAIL;
  }

  const char *prefix = "/";
  char *fichero = (char*)malloc(strlen(nombre)+2);
  strcpy(fichero,prefix);
  strcat(fichero,nombre);

  struct admin padmin = {0,sizeof(int)* tamano,0};
  struct area *pArea = (struct area*) dir;
  *pArea->nombre = *fichero;
  pArea->admin = padmin;
  pArea->buffer = (intptr_t)(dir + sizeof(struct area));

  close(fd);
  return EXIT_SUCCESS;
}


