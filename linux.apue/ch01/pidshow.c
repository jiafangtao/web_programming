#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t pid = getpid();
	pid_t ppid = getppid();

	printf("pid: %d, parent pid: %d\n", pid, ppid);
}
