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

void	my_print(t_data *data, unsigned long time, int n_philo, char *str)
{
	pthread_mutex_lock(&(data->m));
	printf("%ld %d %s\n", time, n_philo, str);
	pthread_mutex_unlock(&(data->m));
}

int	check_for_starvation(t_philo *ph)
{
	if ((my_get_time() - ph->data->last_meal) > (ph->data->t_die + 10))
		return -1;
	return (0);
}

void	*philo_act(void *philo)
{
	t_philo	*ph;
	int		index;

	ph = (t_philo *)philo;
	index = ph->n - 1;
	while (1)
	{
		pthread_mutex_lock(&(ph->data->forks[index]));
		my_print(ph->data, (my_get_time() - ph->data->start), ph->n, "has taken a fork 🍴");
		pthread_mutex_lock(&(ph->data->forks[(index + 1) % ph->data->philo_fork]));
		// if (check_for_starvation(ph) < 0)
		// {
		// 	my_print(ph->data, ph->n, "died 🪦");
		// 	exit(1);
		// }
		ph->data->last_meal = my_get_time();
		my_print(ph->data, (my_get_time() - ph->data->start), ph->n, "has taken a fork 🍴");
		my_print(ph->data, (my_get_time() - ph->data->start), ph->n, "is eating 🍽");
		my_usleep(ph->data->t_eat);
		pthread_mutex_unlock(&(ph->data->forks[index]));
		pthread_mutex_unlock(&(ph->data->forks[(index + 1) % ph->data->philo_fork]));
		my_print(ph->data, (my_get_time() - ph->data->start), ph->n, "is sleeping 😴");
		my_usleep(ph->data->t_sleep);
		my_print(ph->data, (my_get_time() - ph->data->start), ph->n, "is thinking 🤔");
	}
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
		ph[data.i].data = &data;
		ph[data.i].n = data.i + 1;
		(pthread_create(&(ph[data.i].philo), NULL, philo_act, (void *)&ph[data.i]) < 0) &&
			ft_error("your thread fail to be created\n", 31);
	}
	data.i = -1;
	while (++data.i < data.philo_fork)
		pthread_join(ph[data.i].philo, NULL);
	free(ph);
	free(data.forks);
}

