#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
	int sockets[2], child;
	char buf[1024];

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0) {
		perror("opening stream socket pair");
		exit(1);
	}

	if ((child = fork()) == -1)
		perror("fork");
	else if (child) {
		/* This is the parent since value of `child` will be non-zero if it's
		 * the child process */

		/* close one socket because communication is duplex per socket. We will
		 * use the second socket from the socket pair to read messages from the
		 * child process */
		close(sockets[0]);

		/* Read from the second socket. We will use this socket for reading and
		 * writing from the parent */
		if (read(sockets[1], buf, 1024) < 0)
			perror("reading stream message");
		printf("inside parent -->%s\n", buf);
		if (write(sockets[1], "Sending from parent", sizeof("Sending from parent")) < 0)
			perror("writing stream message");
		/* close the parent socket once the writing is done */
		close(sockets[1]);
	} else {
		/* close the parent socket here since we use the first socket for
		 * sending/receiving data from the child */
		close(sockets[1]);

		/* send data from child */
		if (write(sockets[0], "Sending from child", sizeof("Sending from child")) < 0)
			perror("Writing stream message");
		/* read data from child */
		if (read(sockets[0], buf, 1024) < 0)
			perror("reading stream message");
		printf("inside child -->%s\n", buf);
		/* close the child socket once read and write is done */
		close(sockets[0]);
	}

	return 0;
}
