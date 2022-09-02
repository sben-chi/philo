/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 10:36:01 by sben-chi          #+#    #+#             */
/*   Updated: 2022/09/02 15:18:32 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(char *str, int len)
{
	write(2, "Error: ", 7);
	write(2, str, len);
	exit (1);
}

int	ft_atoi(const char *str)
{
	long long	nb;

	nb = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-') 
		(ft_error("your input is < 0\n", 18));
	str += (*str == '+');
	while (*str >= 48 && *str <= 57)
	{
		nb = (nb * 10) + (*str - 48);
		str++;
	}
	if (*str || (nb > 2147483647) || (nb < -2147483648) || !nb)
		ft_error("out of range/your input is an alphanum\n", 39);
	return (nb);
}

unsigned int	my_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	my_usleep(unsigned int t)
{
	struct timeval	time;
	unsigned int	start;

	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (my_get_time() - start < t)
		usleep(20);
}

void	my_print(t_philo *ph, char *str)
{
	unsigned int	t;

	t = (my_get_time() - ph->data->start);
	sem_wait(ph->data->msg);
	printf("%d %d %s\n", t, ph->n, str);
	sem_post(ph->data->msg);
}
