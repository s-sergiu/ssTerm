#define _XOPEN_SOURCE 600
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int open_pty_pair (int *amaster, int *aslave) {
  int master, slave;
  char *name;

  master = posix_openpt (O_RDWR | O_NOCTTY);

  grantpt (master);
  unlockpt (master);

  name = ptsname(master);
  slave = open(name, O_RDWR);

  *amaster = master;
  *aslave = slave;

  return 1;
}

int main(void) {
	int master;
	int slave;
	int result;

	result = open_pty_pair(&master, &slave);
	printf("result is: %d\n", result);	
	printf("master is %d and slave is %d \n", master, slave);	
	return (0);
}
