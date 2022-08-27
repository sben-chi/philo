#include "philo.h"
#include <signal.h>

int main()
{
    sem_t   *t;
    // int     sig;

//    sig = SIGCHLD;
    // printf("%d\n", sig);
    sem_unlink("hello");
    t = sem_open("hello", O_CREAT, 0644, 3);
    if (!fork())
    {
        sem_wait(t);
        sem_wait(t);
        exit (SIGCHLD);
    }
    if (!waitpid(-1, NULL, 1) || data->m)   while(!kill(-1, SIGKILL));
    printf("%d\n", sig);
    return 0;
}