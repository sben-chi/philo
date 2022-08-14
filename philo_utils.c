#include "philo.h"

ph_info	*new(int i)
{
	ph_info *new;

	new = malloc(sizeof(ph_info));
	if (!new)
		return (NULL);
	new->forks[i] = lfork;
	new->rfork = rfork;
	new->next = NULL;
}

void	add_back(ph_info **philo, ph_philo **last, ph_philo *new)
{
	if (!(*philo))
	{
		*philo = new;
		*last = *philo;
	}
	else if (!new)
		return ;
	else
	{
		(*last)->next = new;
		(*last) = (*last)->next;
	}
}


