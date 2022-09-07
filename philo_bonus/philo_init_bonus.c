/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:36:33 by sben-chi          #+#    #+#             */
/*   Updated: 2022/09/07 10:36:40 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data	*init_data(int ac, char **av)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->i = -1;
	data->philo_fork = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	sem_unlink("meals");
	data->meals = sem_open("meals", O_CREAT, 0644, data->philo_fork);
	sem_unlink("nb");
	data->nb = sem_open("nb", O_CREAT, 0644, 0);
	sem_unlink("msg");
	data->msg = sem_open("msg", O_CREAT, 0644, 1);
	return (data);
}

void	create_philos(t_philo *ph, t_data *data, sem_t *forks)
{
	int	pid;

	ph->data = data;
	ph->last_meal = 0;
	ph->n = ph->data->i + 1;
	ph->forks = forks;
	pid = fork();
	if (pid < 0)
		ft_error("fork function\n", 1);
	if (!pid)
		philo_act(ph);
	ph->philo = pid;
}
