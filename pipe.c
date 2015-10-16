#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int sockets[2], child;

	if (pipe(sockets) < 0) {
		perror("opening stream socket pair");
		exit(10);
	}

	if ((child = fork()) == -1)
		perror("fork");
	else if (child) {
		/* parent */

		char buf[1024];
		/* Close the write end in the parent, because we can't really write in
		 * the parent and read from child in case of pipe */
		close(sockets[1]);
		if (read(sockets[0], buf, 1024) < 0)
			perror("reading message");
		printf("-->%s\n", buf);
		/* reading is over, close the read end of the pipe */
		close(sockets[0]);
	} else {
		/* child */

		/* close the read end of the pipe in the child */
		/* Note that the pipe is available both in the child and parent since
		 * any forked process will share the parent's file descriptor table */
		close(sockets[0]);
		if (write(sockets[1], "This is data", sizeof("This is data")) < 0)
			perror("writing message");
		/* close the write end of the pipe in child after writing */
		close(sockets[1]);
	}

	return 0;
}
