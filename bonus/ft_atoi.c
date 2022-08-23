#include "philo.h"

int	ft_error(char *str, int len)
{
	write(2, "Error: ", 7);
	write(2, str, len);
	exit(1);
	return (1);
}

int	ft_atoi(const char *str)
{
	long long	nb;
	int			sign;

	nb = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		nb = (nb * 10) + (*str - 48);
		str++;
	}
	nb = nb * sign;
	if (*str || (nb > 2147483647) || (nb < -2147483648))
		ft_error("out of range/your input is an alphanum\n", 39);
	return (nb);
}
