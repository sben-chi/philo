#include "bonus/philo.h"
#include <signal.h>

int main()
{
    sem_t   *t;
	pid_t	pid;
    // int     sig;
	
//    sig = SIGCHLD;
    // printf("%d\n", sig);
    sem_unlink("hello");
    t = sem_open("hello", O_CREAT, 0644, 4);
    pid = fork();
	if (!pid)
    {
        sem_wait(t);
        sem_wait(t);
    }
	int *i = (int *)t;
	printf("%d\n", *i);
	wait(NULL);
    return 0;
}
