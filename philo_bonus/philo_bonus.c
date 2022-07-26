/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 14:12:54 by sben-chi          #+#    #+#             */
/*   Updated: 2022/09/13 13:46:26 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_meals(t_data *data)
{
	int		n;

	n = -1;
	while (++n < data->philo_fork)
		sem_wait(data->nb);
	exit(0);
}

void	*check_starvation(void *philo)
{
	unsigned int	t;
	t_philo			*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		sem_wait(ph->last_m);
		t = (my_get_time() - ph->data->start - ph->last_meal);
		sem_post(ph->last_m);
		if (t > (ph->data->t_die))
		{
			my_print(ph, "died ", 1);
			exit (0);
		}
	}
}

void	do_something(t_philo *ph)
{
	sem_wait(ph->forks);
	my_print(ph, "has taken a fork 🍴", 0);
	sem_wait(ph->forks);
	my_print(ph, "has taken a fork 🍴", 0);
	my_print(ph, "is eating 🍽", 0);
	sem_wait(ph->last_m);
	ph->last_meal = my_get_time() - ph->data->start;
	sem_post(ph->last_m);
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
	while (1)
	{
		do_something(ph);
		if (ph->data->nb_eat > 0 && ++nb && nb == ph->data->nb_eat)
			sem_post(ph->data->nb);
		my_print(ph, "is sleeping 😴", 0);
		my_usleep(ph->data->t_sleep);
		my_print(ph, "is thinking 🤔", 0);
	}
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_philo		*ph;
	sem_t		*forks;

	data = init_data(ac, av);
	if (!data)
		return (ft_error("invalid argument\n", 18));
	ph = malloc(sizeof(t_philo) * data->philo_fork);
	if (!ph)
		return (0);
	sem_unlink("forks");
	forks = sem_open("forks", O_CREAT, 0644, data->philo_fork);
	data->start = my_get_time();
	while (++data->i < data->philo_fork)
		create_philos(&ph[data->i], data, forks);
	if (data->nb_eat > 0 && !fork())
		check_meals(data);
	waitpid(-1, NULL, 0);
	data->i = -1;
	while (++data->i < data->philo_fork)
		kill(ph[data->i].philo, SIGKILL);
	return (0);
}
