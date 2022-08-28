#include "bonus/philo.h"
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
    }
    printf("%ld\n", t->__align);
    return 0;
}