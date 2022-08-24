#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdio.h>

typedef struct data
{
	int				philo_fork;
	int				i;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	t_die;
	unsigned int	start;
	int				nb_eat;
	sem_t			*meals;
	sem_t			*nb;
	sem_t			*msg;
}t_data;

typedef struct philo
{
	int				n;
	unsigned int	last_meal;
	sem_t			*forks;
	t_data			*data;
	pthread_t		philo;
}t_philo;

int ft_atoi(const char *str);
int ft_error(char *str, int len);

#endif
