/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 14:12:54 by sben-chi          #+#    #+#             */
/*   Updated: 2022/09/01 12:16:15 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_meals(void *philo)
{
	t_philo	*ph;
	int		n;
	int		i;

	n = 0;
	i = -1;
	ph = (t_philo *)philo;
	while (n < ph->data->philo_fork)
	{
		sem_wait(ph->data->nb);
		n++;
	}
	while (++i < ph->data->philo_fork)
		kill(ph[i].philo, SIGKILL);
	exit(0);
	return (NULL);
}

void	*check_starvation(void *philo)
{
	unsigned int	t;
	t_philo			*ph;
	unsigned	int i;

	ph = (t_philo *)philo;
	while (1)
	{
		i = my_get_time();
		t = (i - ph->data->start - ph->last_meal);
		if (t > (ph->data->t_die))
		{
			printf("i => %d start => %d last => %d t => %d t_die => %d\n", i, ph->data->start, ph->last_meal, t, ph->data->t_die);
			my_print(ph, "died ");
			exit (0);
		}
		usleep(10);
	}
	return (NULL);
}

void	do_something(t_philo *ph)
{
	sem_wait(ph->forks);
	my_print(ph, "has taken a fork 🍴");
	sem_wait(ph->forks);
	ph->last_meal = my_get_time() - ph->data->start;
	my_print(ph, "has taken a fork 🍴");
	my_print(ph, "is eating 🍽");
	my_usleep(ph->data->t_eat);
	sem_post(ph->forks);
	sem_post(ph->forks);
}

void	philo_act(t_philo *ph)
{
	int			nb;
	pthread_t	t;

	nb = 0;
	pthread_create(&t, NULL, check_starvation, (void *)ph);
	if ((ph->n - 1) % 2)
		usleep(50);
	while (1)
	{
		do_something(ph);
		my_print(ph, "is sleeping 😴");
		my_usleep(ph->data->t_sleep);
		if (ph->data->nb_eat > 0 && ++nb && nb == ph->data->nb_eat)
			sem_post(ph->data->nb);
		my_print(ph, "is thinking 🤔");
	}
}

void	init_data(t_data *data, int ac, char **av)
{
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
	data->meals = sem_open("meals", O_CREAT, 0644, data->philo_fork);
	sem_unlink("nb");
	data->nb = sem_open("nb", O_CREAT, 0644, 0);
	sem_unlink("msg");
	data->msg = sem_open("msg", O_CREAT, 0644, 1);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_philo		*ph;
	int			i;
	int			pid;
	sem_t		*forks;
	pthread_t	t;

	i = -1;
	if (ac != 6 && ac != 5)
		return (0);
	data = malloc(sizeof(t_data));
	ph = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!data || !ph)
		return (1);
	init_data(data, ac, av);
	sem_unlink("forks");
	forks = sem_open("forks", O_CREAT, 0644, data->philo_fork);
	data->start = my_get_time();
	while (++i < data->philo_fork)
	{
		ph[i].data = data;
		ph[i].last_meal = 0;
		ph[i].n = i + 1;
		ph[i].forks = forks;
		pid = fork();
		if (!pid)
			philo_act(&ph[i]);
		ph[i].philo = pid;
		
	}
	if (data->nb_eat > 0)
		pthread_create(&t, NULL, check_meals, (void *)ph);
	i = -1;
	waitpid(-1, NULL, 0);
	while (++i < data->philo_fork)
		kill(ph[i].philo, SIGKILL);
	return (0);
}
