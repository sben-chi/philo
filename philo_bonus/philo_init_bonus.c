/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:36:33 by sben-chi          #+#    #+#             */
/*   Updated: 2022/09/11 14:22:34 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	len_nbr(int n)
{
	int	len;

	len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*name;

	len = len_nbr(n);
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		return (NULL);
	name[len] = '\0';
	if (!n)
		*name = 48;
	while (len > 0 && n)
	{
		name[--len] = n % 10 + 48;
		n /= 10;
	}
	return (name);
}

t_data	*init_data(int ac, char **av)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data || (ac != 6 && ac != 5))
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
	int		pid;
	char	*name;

	ph->data = data;
	ph->last_meal = 0;
	ph->n = ph->data->i + 1;
	ph->forks = forks;
	name = ft_itoa(ph->data->i);
	sem_unlink(name);
	ph->last_m = sem_open(name, O_CREAT, 0644, 1);
//	pthread_mutex_init(&(ph->last_m), NULL);
	pid = fork();
	if (pid < 0)
		ft_error("fork() error\n", 1);
	if (!pid)
		philo_act(ph);
	ph->philo = pid;
	free(name);
	usleep(10);	
}
