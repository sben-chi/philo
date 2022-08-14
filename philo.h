#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

typedef struct data
{
	int				philo_fork;
	int				i;
	int				state;
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				nb_eat;
	int				nb_philo;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m;
}t_data;

int ft_atoi(const char *str);
int ft_error(char *str, int len);

#endif
