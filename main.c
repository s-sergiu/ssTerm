#define _XOPEN_SOURCE 600
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
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

char buffer[1000];
int create_p(int *master, int *slave) {
	int p;
	char *env = NULL;

	p = fork();
	if (p == 0)
	{
		close(*master);

		setsid();
		if (ioctl(*slave, TIOCSCTTY, NULL) == -1)
		{
			perror("ioctl(TIOCSCTTY)");
			return 0;
		}

		dup2(*slave, 0);
		dup2(*slave, 1);
		dup2(*slave, 2);
		close(*slave);

		printf("executing \n");
		execle("/bin/bash", "/bin/who", NULL, env);
	}
	while(waitpid(p, NULL, WNOHANG) > 0)
		;
	read(*master, buffer, 1000);
	return 1;
}

int main(void) {
	int master;
	int slave;
	int result;

	result = open_pty_pair(&master, &slave);
	printf("result is: %d\n", result);	
	printf("master is %d and slave is %d \n", master, slave);	

	printf("Creating process\n");	
	create_p(&master,&slave);
	printf("stopping process\n");	
	return (0);
}
