/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 14:32:44 by sben-chi          #+#    #+#             */
/*   Updated: 2022/09/02 16:11:32 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdio.h>
# include <signal.h>

typedef struct data
{
	int				philo_fork;
	int				i;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	t_die;
	unsigned int	start;
	int				nb_eat;
	sem_t			*meals;
	sem_t			*nb;
	sem_t			*msg;
}t_data;

typedef struct philo
{
	int				n;
	unsigned int	last_meal;
	sem_t			*forks;
	t_data			*data;
	pid_t			philo;
}t_philo;

int				ft_atoi(const char *str);
int				ft_error(char *str, int len);
unsigned int	my_get_time(void);
void			my_usleep(unsigned int t);
void			my_print(t_philo *ph, char *str, short b);
t_data			*init_data(int ac, char **av);
void			create_philos(t_philo *ph, t_data *data, sem_t *forks);
void			philo_act(t_philo *ph);

#endif
