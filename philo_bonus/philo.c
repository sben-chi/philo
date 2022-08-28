/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 14:12:54 by sben-chi          #+#    #+#             */
/*   Updated: 2022/08/28 17:42:45 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_starvation(t_philo *ph)
{
	unsigned int	t;
	t = (my_get_time() - ph->data->start - ph->last_meal);
//	printf("start %d    last_meal %d\n", ph->data->start, ph->last_meal);
	if (t > (ph->data->t_die))
	{
		my_print(ph, "died ", 1);
	//	printf("==>%d\n", t);
		exit (0);
	}
	return (1);
}

void	take_forks(t_philo *ph)
{
	sem_wait(ph->forks);
	my_print(ph, "has taken a fork 🍴", 0);
	if (ph->data->philo_fork == 1)
	{
		my_usleep(ph->data->t_die + 1);
		return ;
	}
	sem_wait(ph->forks);
	check_starvation(ph);
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
	pthread_t	t;

	nb = 0;
	while (1)
	{
		take_forks(ph);		
		ph->last_meal = my_get_time() - ph->data->start;
		
		eat(ph);
		release_forks(ph);
		my_print(ph, "is sleeping 😴", 0);
		my_usleep(ph->data->t_sleep);
		nb++;
		if (ph->data->nb_eat > 0 && nb == ph->data->nb_eat)
			exit(0);
	//	printf("philo %d eat %d and rest_m %d\n", ph->n, nb, ph->data->i);
		my_print(ph, "is thinking 🤔", 0);
	}
}

void	init_data(t_data *data, int ac, char **av)
{
	int	i;

	i = -1;
	printf("%d\n", data->start);
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
	int		sig;
	pthread_t t;

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
//	printf("%d\n", data->start);
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
		{
			philo_act(&ph[i]);
		}
		ph[i].philo = pid;
	}
	if (data->nb_eat < 0)
	{
		waitpid(-1, NULL, 0);
		i = -1;
		while (++i < data->philo_fork)
			kill(ph[i].philo, SIGKILL);
	}
	else
	{	
		i = -1;
		while (++i < data->philo_fork)
			waitpid(ph[i].philo, NULL, 0);
	}
	// create a thread to check starvation
	// exit child if nb == nb_meals
	return (0);
}
