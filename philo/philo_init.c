/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:59:23 by sben-chi          #+#    #+#             */
/*   Updated: 2022/09/07 09:59:26 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	static int	err;
	static int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_fork);
	if (!data->forks)
		return (0);
	err += pthread_mutex_init(&(data->msg), NULL);
	err += pthread_mutex_init(&(data->meals), NULL);
	err += pthread_mutex_init(&(data->increment), NULL);
	err += pthread_mutex_init(&(data->last_m), NULL);
	while (i < data->philo_fork)
		err += pthread_mutex_init(&(data->forks[i++]), NULL);
	return (!(err && ft_error("your mutex object fail to be created :(\n", 40)));
}

t_data	*init_data(int ac, char **av)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_fork = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	if ((data->philo_fork < 0) || ((int)data->t_die < 0)
		|| ((int)data->t_eat < 0) || (int)data->t_sleep < 0 || !data->nb_eat)
		return (NULL);
	data->ph_f = data->philo_fork;
	if (!init_mutex(data))
		return (NULL);
	return (data);
}
