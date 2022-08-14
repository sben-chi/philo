#include "philo.h"
#include <sys/time.h>

void	critical_section(t_data *ph)
{
	if (ph->philo)
}

void	philo_act(void	*data)
{
	t_data	*ph;
	int		nb;

	ph = (t_data *)data;
	nb = (ph->ac == 6) * ph->nb_eat;
	if (ph->ac == 5)
		nb = 3;
	while (nb--)
	{
		printf("%d think\n", ph->i + 1);
		pthread_mutex_lock(&ph->m);
		printf("%d has taken a fork\n", ph->i + 1);
		printf("%d is eating\n", ph->i + 1);
		usleep(ph->t_eat / 1000);
		printf("%d is sleeping\n", ph->i + 1);
		usleep(ph->t_sleep / 1000);
	}
}

int main(int ac, char **av)
{
	pthread_t	*philos;
	t_data	ph;

	ph.i = -1;
	if (ac != 6 && ac != 5)
		return (0);
	ph.philo_fork = ft_atoi(av[1]);
	philos = malloc(sizeof(pthread_t) * ph.philo_fork);
	if (!philos)
		return (0);
	pthread_mutex_init(&ph.m, NULL);
	ph.t_die = ft_atoi(av[2]);
	ph.t_eat = ft_atoi(av[3]);
	ph.t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		ph.nb_eat = ft_atoi(av[5]);
	ph.ac = ac;
	if (pthread_mutex_init(&(ph.m), NULL))
		ft_error("your mutex object fail to be created :(\n", 40);
	while(++(ph.i) < ph.philo_fork)
	{
		if (pthread_create(&philos[ph.i], NULL, philo_act, &ph) < 0)
		{
			free(philos);
			ft_error("your thread fail to be created\n", 31);
		}
	}
	ph.i = -1;
	while(++(ph.i) < ph.philo_fork)
		pthread_join(philos[ph.i], NULL);
	pthread_mutex_destroy(&ph.m);
}

/*	static struct timeval timestamp;
	timestamp.tv_usec = 0;
	printf("%d\n", timestamp.tv_usec);
	usleep(500000);
	gettimeofday(&timestamp, NULL);
	printf("%d\n", timestamp.tv_usec);*/

