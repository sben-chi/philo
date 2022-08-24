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
	// sem_wait(ph->data->msg);
	printf("%d %d %s\n", t, ph->n, str);
	// if (!b)
		// sem_post(ph->data->msg);
}

int	check_starvation(t_philo *ph)
{
	unsigned int t;
	
	t = (my_get_time() - ph->data->start - ph->last_meal);
	if (t > (ph->data->t_die)) //+ 100))
	{
		my_print(ph, "died 🪦", 1);
		printf("==>%d\n", t);
		return (0);
	}
	return (1);
}

void	take_forks(t_philo *ph)
{
	sem_wait(ph->forks);
	my_print(ph, "has taken a fork 🍴", 0);
	sem_wait(ph->forks);
	my_print(ph, "has taken a fork 🍴", 0);
}

void	release_forks(t_philo *ph)
{
	sem_post(ph->forks);
	sem_post(ph->forks);
}

void	eat(t_philo *ph)
{
	my_print(ph, "is eating 🍽", 0);
	my_usleep(ph->data->t_eat);
}

void	philo_act(t_philo *ph)
{
	int	nb;

	nb = 0;
	while (check_starvation(ph))
	{
		take_forks(ph);
		ph->last_meal = my_get_time() - ph->data->start;
		eat(ph);
		release_forks(ph);
		my_print(ph, "is sleeping 😴", 0);
		my_usleep(ph->data->t_sleep);
		nb++;
		// if (ph->data->nb_eat > 0 && nb == ph->data->nb_eat)
		// 	ph->data->i--;
		// printf("philo %d eat %d and rest_m %d\n", ph->n, nb, ph->data->i);
		my_print(ph, "is thinking 🤔", 0);
	}
	// printf("ph %d\n", ph->n);
	exit(1);

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
	sem_unlink("meals");
	data->meals = sem_open("meals", O_CREAT);
	sem_unlink("nb");
	data->nb = sem_open("nb", O_CREAT);
	sem_unlink("msg");
	data->msg = sem_open("msg", O_CREAT);
}

int main(int ac, char **av)
{
	t_data	*data;
	struct timeval time;
	t_philo	*ph;
	int		i;
	int		pid;
	sem_t	*forks;

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
	sem_unlink("forks");
	forks = sem_open("forks", O_CREAT, 0644, data->philo_fork);
	gettimeofday(&time, NULL);
	data->start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while(++i < data->philo_fork)
	{
		ph[i].data = data;
		ph[i].last_meal = 0;
		ph[i].n = i + 1;
		ph[i].forks = forks;
		if (i % 2)
			usleep(50);
		pid = fork();
		if (!pid)
			philo_act(&ph[i]);
	}
	wait(NULL);
	return (0);
}