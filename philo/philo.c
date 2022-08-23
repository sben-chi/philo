#include "philo.h"

unsigned int my_get_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	my_usleep(unsigned int t)
{
	struct timeval		time;
	unsigned int	start;

	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (my_get_time() - start < t);
}

void	my_print(t_philo *ph, char *str, short b)
{
	unsigned int	t;

	t = (my_get_time() - ph->data->start);
	pthread_mutex_lock(&(ph->data->m));
	printf("%d %d %s\n", t, ph->n, str);
	if (!b)
		pthread_mutex_unlock(&(ph->data->m));
}

int	check_for_starvation(t_philo *ph)
{
	unsigned int t;
	unsigned int	last_meal;

	pthread_mutex_lock(&ph->data->last_m);
	last_meal = ph->last_meal;
	pthread_mutex_unlock(&ph->data->last_m);
	t = (my_get_time() - ph->data->start - last_meal);
	if (t > (ph->data->t_die)) //+ 100))
	{
		my_print(ph, "died 🪦", 1);
		printf("==>%d\n", t);
		return (0);
	}
	return (1);
}

void	take_forks(t_philo *ph, int index)
{
	pthread_mutex_lock(&(ph->data->forks[index]));
	my_print(ph, "has taken a fork 🍴", 0);
	pthread_mutex_lock(&(ph->data->forks[(index + 1) % ph->data->philo_fork]));
	my_print(ph, "has taken a fork 🍴", 0);
}

void	release_forks(t_philo *ph, int index)
{
	pthread_mutex_unlock(&(ph->data->forks[index]));
	pthread_mutex_unlock(&(ph->data->forks[(index + 1) % ph->data->philo_fork]));
}

void	eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->last_m);
	ph->last_meal = my_get_time() - ph->data->start;
	pthread_mutex_unlock(&ph->data->last_m);
	my_print(ph, "is eating 🍽", 0);
	my_usleep(ph->data->t_eat);
}

void	*philo_act(void *philo)
{
	t_philo		*ph;
	int			index;
	static int	i;
	int			nb;

	ph = (t_philo *)philo;
	pthread_mutex_lock(&ph->data->increment);
	index = i++;
	ph->n = i;
	pthread_mutex_unlock(&ph->data->increment);
	if (index % 2)
		usleep(50);
	nb = 0;
	while (1)
	{
		take_forks(ph, index);
		eat(ph);
		release_forks(ph, index);
		my_print(ph, "is sleeping 😴", 0);
		my_usleep(ph->data->t_sleep);
		pthread_mutex_lock(&ph->data->meals);
		nb++;
		if (ph->data->nb_eat > 0 && nb == ph->data->nb_eat)
			ph->data->i--;
		// printf("philo %d eat %d and rest_m %d\n", ph->n, nb, ph->data->i);
		pthread_mutex_unlock(&ph->data->meals);
		my_print(ph, "is thinking 🤔", 0);
	}
	return (NULL);
}

void	init_data(t_data *data, int ac, char **av)
{
	int	i;
	
	i = -1;
	data->philo_fork = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	data->i = data->philo_fork;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_fork);
	if (!data->forks)
		exit(1);
	(pthread_mutex_init(&(data->m), NULL)) &&
			ft_error("your mutex object fail to be created :(\n", 40);
	(pthread_mutex_init(&(data->meals), NULL)) &&
			ft_error("your mutex object fail to be created :(\n", 40);
	(pthread_mutex_init(&(data->increment), NULL)) &&
			ft_error("your mutex object fail to be created :(\n", 40);
	(pthread_mutex_init(&(data->last_m), NULL)) &&
			ft_error("your mutex object fail to be created :(\n", 40);
	while (++i < data->philo_fork)
		(pthread_mutex_init(&(data->forks[i]), NULL)) &&
			ft_error("your mutex object fail to be created :(\n", 40);
	
}

int main(int ac, char **av)
{
	t_data	*data;
	struct timeval time;
	t_philo	*ph;
	int		i;

	i = -1;
	if (ac != 6 && ac != 5)
		return(0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_data(data, ac, av);
	ph = malloc(sizeof(t_philo) * data->philo_fork);
	if (!ph)
		return (1);
	ph->last_meal = 0;
	gettimeofday(&time, NULL);
	data->start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while(++i < data->philo_fork)
	{
		ph[i].data = data;
		(pthread_create(&(ph[i].philo), NULL, philo_act, (void *)&ph[i]) < 0) &&
			ft_error("your thread fail to be created\n", 31);
	}
	while (check_for_starvation(ph) && data->i);
	return (0);
}