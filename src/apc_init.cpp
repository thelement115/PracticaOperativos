#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include "apc.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdint>

using namespace std;

int APC_Init(const char* nombre, size_t tamano) {

  int fd = shm_open(nombre, O_RDWR | O_CREAT | O_EXCL, 0660);

  if (fd < 0) {
    cerr << "Error creando la memoria compartida: "
	  << errno << strerror(errno) << endl;
    exit(1);
  }

  if (ftruncate(fd, sizeof(struct area) + sizeof(int)* tamano) != 0) {
    cerr << "Error creando la memoria compartida: "
	  << errno << strerror(errno) << endl;
    exit(1);
  }

  void *dir;

  if ((dir = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED,
		  fd, 0)) == MAP_FAILED) {
    cerr << "Error mapeando la memoria compartida: "
	  << errno << strerror(errno) << endl;
    exit(1);
  }

  const char *prefix = "/";
  char *fichero = (char*)malloc(strlen(nombre)+2);
  strcpy(fichero,prefix);
  strcat(fichero,nombre);

  struct admin padmin = {0,tamano,0};
  struct area *pArea = (struct area*) dir;
  *pArea->nombre = *fichero;
  pArea->admin = padmin;
  pArea->buffer = (intptr_t)(dir + sizeof(struct area));

  close(fd);
  return EXIT_SUCCESS;
}


