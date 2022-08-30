/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 10:35:45 by sben-chi          #+#    #+#             */
/*   Updated: 2022/08/28 18:11:02 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_starvation(t_philo *ph)
{
	unsigned int	t;
	unsigned int	last_meal;

	pthread_mutex_lock(&ph->data->last_m);
	last_meal = ph->last_meal;
	pthread_mutex_unlock(&ph->data->last_m);
	t = (my_get_time() - ph->data->start - last_meal);
	if (t > (ph->data->t_die))
	{
		my_print(ph, "died 🪦", 1);
		return (0);
	}
	return (1);
}

void	do_something(t_philo *ph, int index)
{
	pthread_mutex_lock(&(ph->data->forks[index]));
	my_print(ph, "has taken a fork 🍴", 0);
	pthread_mutex_lock(&(ph->data->forks[(index + 1) % ph->data->philo_fork]));
	my_print(ph, "has taken a fork 🍴", 0);
	pthread_mutex_lock(&ph->data->last_m);
	ph->last_meal = my_get_time() - ph->data->start;
	pthread_mutex_unlock(&ph->data->last_m);
	my_print(ph, "is eating 🍽", 0);
	my_usleep(ph->data->t_eat);
	pthread_mutex_unlock(&(ph->data->forks[index]));
	pthread_mutex_unlock(&(ph->data->forks[(index + 1)
			% ph->data->philo_fork]));
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
		do_something(ph, index);
		pthread_mutex_lock(&ph->data->meals);
		if (++nb && nb == ph->data->nb_eat)
			ph->data->ph_f--;
		pthread_mutex_unlock(&ph->data->meals);
		my_print(ph, "is sleeping 😴", 0);
		my_usleep(ph->data->t_sleep);
		my_print(ph, "is thinking 🤔", 0);
	}
	return (NULL);
}

int	init_data(t_data *data, int ac, char **av)
{
	static int	i;
	static int	err;

	data->philo_fork = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	if ((data->philo_fork < 0) || ((int)data->t_die < 0)
		|| ((int)data->t_eat < 0) || (int)(data->t_sleep < 0) || !data->nb_eat)
		return (1);
	data->ph_f = data->philo_fork;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_fork);
	if (!data->forks)
		return (1);
	err += pthread_mutex_init(&(data->msg), NULL);
	err += pthread_mutex_init(&(data->meals), NULL);
	err += pthread_mutex_init(&(data->increment), NULL);
	err += pthread_mutex_init(&(data->last_m), NULL);
	while (i < data->philo_fork)
		err += pthread_mutex_init(&(data->forks[i++]), NULL);
	return (err && ft_error("your mutex object fail to be created :(\n", 40));
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*ph;
	int		i;

	i = -1;
	if (ac != 6 && ac != 5)
		return (ft_error("invalid arguments\n", 18));
	data = malloc(sizeof(t_data));
	ph = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!data || !ph)
		return (0);
	if (init_data(data, ac, av))
		return (0);
	data->start = my_get_time();
	while (++i < data->philo_fork)
	{
		ph[i].data = data;
		ph[i].last_meal = 0;
		(pthread_create(&(ph[i].philo), NULL, philo_act, (void *)&ph[i]) < 0) &&
			ft_error("your thread fail to be created\n", 31);
	}
	while (check_starvation(ph) && data->ph_f)
	{
	}
	return (0);
}
