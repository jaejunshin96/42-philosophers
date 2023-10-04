/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:56:59 by jaeshin           #+#    #+#             */
/*   Updated: 2023/10/04 11:09:20 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *p, long long start_time, int state)
{
	long long	time;

	time = get_time() - start_time;
	pthread_mutex_lock(&p->args->print);
	if (state == FORK)
		printf("%lldms philo %d has taken a fork.\n", time, p->id);
	else if (state == EAT)
		printf("%lldms philo %d is eating.\n", time, p->id);
	else if (state == SLEEP)
		printf("%lldms philo %d is sleeping.\n", time, p->id);
	else if (state == THINK)
		printf("%lldms philo %d is thinking.\n", time, p->id);
	else
		printf("%lldms philo %d died.\n", time, p->id);
	pthread_mutex_unlock(&p->args->print);
}

void	print_if_all_eaten(t_total *total)
{
	int	i;

	i = -1;
	while (total->args->nbr_of_must_eat > 0 && \
		++i < total->philos->args->nbr_of_phil)
	{
		if (total->philos[i].count_of_eat < total->args->nbr_of_must_eat)
			break ;
		if (i + 1 == total->args->nbr_of_phil)
			printf("Everyone has eaten %d times.\n", \
				total->args->nbr_of_must_eat);
	}
}
