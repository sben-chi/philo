#include "philo.h"

int my_get_time()
{
	struct timeval		start;
	static unsigned int	time;
	struct timeval		end;

	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	time += (end.tv_sec * 1000) + (end.tv_usec / 1000)
		- (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (time);
}

void	my_usleep(int t)
{
	unsigned int	end;

	end = my_get_time();
	while (my_get_time() < end)
		usleep(t * 1000);
}

void	my_print(int n_philo, char *str)
{
	pthread_mutex_lock(&(data->m));
	printf("%d %d %s\n", my_get_time(), n_philo, str);
	pthread_mutex_unlock(&(data->m));
}

void	philo_act(void *dt)
{
	t_data	data;
	int		n;

	n = data->i;
	data = (t_data *)dt;
	while (1)
	{
		pthread_mutex_lock(&(data->forks[n]));
		pthread_mutex_lock(&(data->forks[(n + 1) % data->philo_fork]));
		my_print(n + 1, "has taken a fork");
		my_usleep(data->t_eat);	
		my_print(n + 1, "is eating");
		pthread_mutex_unlock(&(data->forks[n]));
		pthread_mutex_unlock(&(data->forks[(n + 1) % data->philo_fork]));
		my_print(n + 1, "is sleeping");
		my_usleep(data->t_sleep);
		my_print(n + 1, "is thinking");
	}
}

void	init_data(t_data *data, int ac, char **av)
{
	data->i = 0;
	data->philo_fork = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_fork);
	data->philos = malloc(sizeof(pthread_t) * data->philo_fork);
}

int main(int ac, char **av)
{
	ph_info	last;
	t_data	data;

	if (ac != 6 && ac != 5)
		return(0);
	init_data(&data, ac, av);
	if (!(data.forks) || !(data.philos))
		return (0);
	(pthread_mutex_init(&(data.m), NULL)) &&
			ft_error("your mutex object fail to be created :(\n", 40);
	while (i < data.philo_fork)
		(pthread_mutex_init(&(data.forks[i++]), NULL)) &&
			ft_error("your mutex object fail to be created :(\n", 40);
	data.i = 0;
	while(i < data.philo_fork)
		(pthread_create(&(data.philos[i++]), NULL, philo_act, &data) < 0) &&
			ft_error("your thread fail to be created\n", 31);
	data.i = 0;
	while (i < data.philo_fork)
		pthread_join(data.phils[i++], NULL);
}

