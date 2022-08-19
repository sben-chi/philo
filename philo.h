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
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	t_die;
	unsigned int	last_meal;
	unsigned int	start;
	int				nb_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m;
}t_data;

typedef struct philo
{
	int			n;
	t_data		*data;
	pthread_t	philo;
}t_philo;

int ft_atoi(const char *str);
int ft_error(char *str, int len);

#endif
