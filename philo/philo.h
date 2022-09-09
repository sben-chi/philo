/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:38:27 by sben-chi          #+#    #+#             */
/*   Updated: 2022/09/09 09:17:44 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct data
{
	int				philo_fork;
	int				ph_f;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	t_die;
	unsigned int	start;
	int				nb_eat;
	pthread_mutex_t	meals;
	pthread_mutex_t	last_m;
	pthread_mutex_t	increment;
	pthread_mutex_t	*forks;
	pthread_mutex_t	msg;
}t_data;

typedef struct philo
{
	int				n;
	unsigned int	last_meal;
	t_data			*data;
	pthread_t		philo;
}t_philo;

int				ft_atoi(const char *str);
int				ft_error(char *str, int len);
unsigned int	my_get_time(void);
void			my_print(t_philo *ph, char *str, short b);
t_data			*init_data(int ac, char **av);
int				init_mutex(t_data *data);
void			my_usleep(unsigned int t);

#endif
