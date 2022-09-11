/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 10:35:45 by sben-chi          #+#    #+#             */
/*   Updated: 2022/09/11 13:09:21 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_starvation(t_philo *ph)
{
	unsigned int	t;
	int				i;

	i = -1;
	while (++i < ph->data->philo_fork)
	{
		pthread_mutex_lock(&ph->data->increment);
		pthread_mutex_lock(&ph[i].last_m);
		t = (my_get_time() - ph->data->start - ph[i].last_meal);
		pthread_mutex_unlock(&ph[i].last_m);
		if (t > (ph->data->t_die))
		{
			my_print(ph[i].n, ph->data, "died 😵", 1);
			return (0);
		}
		pthread_mutex_unlock(&ph->data->increment);
		pthread_mutex_lock(&ph->data->meals);
		if (!ph->data->ph_f)
			return (0);
		pthread_mutex_unlock(&ph->data->meals);
	}
	return (1);
}

void	do_something(t_philo *ph, int index, int *nb)
{
	pthread_mutex_lock(&(ph->data->forks[index]));
	my_print(ph->n, ph->data, "has taken a fork 🍴", 0);
	pthread_mutex_lock(&(ph->data->forks[(index + 1) % ph->data->philo_fork]));
	my_print(ph->n, ph->data, "has taken a fork 🍴", 0);
	pthread_mutex_lock(&ph->last_m);
	ph->last_meal = my_get_time() - ph->data->start;
	pthread_mutex_unlock(&ph->last_m);
	my_print(ph->n, ph->data, "is eating 🍽", 0);
	my_usleep(ph->data->t_eat);
	pthread_mutex_unlock(&(ph->data->forks[index]));
	pthread_mutex_unlock(&(ph->data->forks[(index + 1)
			% ph->data->philo_fork]));
	if (ph->data->nb_eat > 0 && ++(*nb))
	{
		pthread_mutex_lock(&ph->data->meals);
		if ((*nb) == ph->data->nb_eat)
			ph->data->ph_f--;
		pthread_mutex_unlock(&ph->data->meals);
	}
}

void	*philo_act(void *philo)
{
	t_philo		*ph;
	int			index;
	int			nb;
	static int	i;

	nb = 0;
	ph = (t_philo *)philo;
	pthread_mutex_lock(&ph->data->increment);
	index = i++;
	ph->n = i;
	pthread_mutex_unlock(&ph->data->increment);
	if (index % 2)
		usleep(50);
	while (1)
	{
		do_something(ph, index, &nb);
		my_print(ph->n, ph->data, "is sleeping 😴", 0);
		my_usleep(ph->data->t_sleep);
		my_print(ph->n, ph->data, "is thinking 🤔", 0);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*ph;
	int		i;

	i = -1;
	data = init_data(ac, av);
	if (!data)
		return (ft_error("invalid argument\n", 18));
	ph = malloc(sizeof(t_philo) * data->philo_fork);
	if (!ph)
		return (0);
	data->start = my_get_time();
	while (++i < data->philo_fork)
	{
		pthread_mutex_init(&(ph[i].last_m), NULL);
		ph[i].data = data;
		ph[i].last_meal = 0;
		if (pthread_create(&(ph[i].philo), NULL, philo_act, (void *)&ph[i]) < 0)
			ft_error("your thread fail to be created\n", 31);
	}
	while (check_starvation(ph))
	{
	}
	return (0);
}
