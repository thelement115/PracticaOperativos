#include "apc.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include "apc.h"


int APC_Terminar(const char *nombre) {
  if(nombre == NULL){
    errno = APC_ERROR_ARGUMENTO;
    return APC_FAIL;
  }
  int fd = shm_unlink(nombre);
  if (fd < 0){
    errno = APC_ERROR_NOEXISTE;
    return APC_FAIL;
  }
  return 0;
}
