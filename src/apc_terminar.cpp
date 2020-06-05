#include "apc.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include "apc.h"


int APC_Terminar(const char *nombre) {
  shm_unlink(nombre);
  return 0;
}
