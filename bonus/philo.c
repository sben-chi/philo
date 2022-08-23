#include "philo.h"

unsigned int my_get_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	my_usleep(int t)
{
	struct timeval		time;
	static unsigned int	start;

	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (my_get_time() - start < t);
}

void	my_print(t_philo *ph, char *str, short b)
{
	unsigned int	t;
	static short	a;

	t = (my_get_time() - ph->data->start);
	if (a)
	{
		pthread_detach(ph->philo);
		a = 1;
		return ;	
	}
	pthread_mutex_lock(&(ph->data->m));
	if (b)
		a = 1;
	printf("%d %d %s\n", t, ph->n, str);
	pthread_mutex_unlock(&(ph->data->m));
}

int	check_for_starvation(t_philo *ph)
{
	unsigned int t;

	t = (my_get_time() - ph->data->start - ph->data->last_meal);
	if (t > ph->data->t_die)
	{
		my_print(ph, "died 🪦", 1);
		return (0);
	}
	return (1);
}

void	*philo_act(void *philo)
{
	t_philo	*ph;
	int		index;
	static int i;

	ph = (t_philo *)philo;
	// index = ph->n - 1;
	index = i++;
	ph->n = i;
	if (index % 2)
		usleep(500);
	// printf("%d %d\n", index, ph->n);
	while (1)
	{
		pthread_mutex_lock(&(ph->data->forks[index]));
		my_print(ph, "has taken a fork 🍴", 0);
		pthread_mutex_lock(&(ph->data->forks[(index + 1) % ph->data->philo_fork]));
		ph->data->last_meal = my_get_time();
		my_print(ph, "has taken a fork 🍴", 0);
		my_print(ph, "is eating 🍽", 0);
		my_usleep(ph->data->t_eat);
		pthread_mutex_unlock(&(ph->data->forks[index]));
		pthread_mutex_unlock(&(ph->data->forks[(index + 1) % ph->data->philo_fork]));
		my_print(ph, "is sleeping 😴", 0);
		my_usleep(ph->data->t_sleep);
		my_print(ph, "is thinking 🤔", 0);
	}
	return (NULL);
}

void	init_data(t_data *data, int ac, char **av)
{
	data->i = -1;
	data->philo_fork = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->last_meal = 0;
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_fork);
	if (!data->forks)
		exit(1);
	(pthread_mutex_init(&(data->m), NULL)) &&
			ft_error("your mutex object fail to be created :(\n", 40);
	while (++data->i < data->philo_fork)
		(pthread_mutex_init(&(data->forks[data->i]), NULL)) &&
			ft_error("your mutex object fail to be created :(\n", 40);
	
}

int main(int ac, char **av)
{
	t_data	data;
	struct timeval time;
	t_philo	*ph;
	if (ac != 6 && ac != 5)
		return(0);
	init_data(&data, ac, av);
	ph = malloc(sizeof(t_philo) * data.philo_fork);
	if (!ph)
		return (1);
	data.i = -1;
	gettimeofday(&time, NULL);
	data.start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while(++data.i < data.philo_fork)
	{
		if (!fork())
			philo_act(ph);
	}
	for (int i = 0; i < data.philo_fork; i++)
		wait(NULL);
	while (check_for_starvation(ph));
	free(ph);
	free(data.forks);
}

