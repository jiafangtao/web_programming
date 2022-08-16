#include <string.h>
#include <stdio.h>
#include <errno.h>

int main()
{
	int error = 2;
	char * msg = strerror(error);
	printf("What is the error? %s\n", msg);

	errno = EACCES;
	perror("perror function to print current error");

	return 0;
}
