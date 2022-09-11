/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 10:36:01 by sben-chi          #+#    #+#             */
/*   Updated: 2022/09/11 12:27:42 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str, int len)
{
	write(2, "Error: ", 7);
	write(2, str, len);
	return (1);
}

int	ft_atoi(const char *str)
{
	long long	nb;

	nb = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		return (-2);
	str += (*str == '+');
	while (*str >= 48 && *str <= 57)
	{
		nb = (nb * 10) + (*str - 48);
		str++;
	}
	if (*str || (nb > 2147483647) || (nb < -2147483648) || !nb)
		return (-2);
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

void	my_print(int n, t_data *data, char *str, short b)
{
	unsigned int	t;

	t = (my_get_time() - data->start);
	pthread_mutex_lock(&(data->msg));
	printf("%d %d %s\n", t, n, str);
	if (!b)
		pthread_mutex_unlock(&(data->msg));
}
