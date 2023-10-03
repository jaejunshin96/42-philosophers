/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:55:01 by jaeshin           #+#    #+#             */
/*   Updated: 2023/10/03 21:34:21 by jaeshin          ###   ########.fr       */
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

long long	get_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		printf("get time erorr\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	result;

	i = 0;
	minus = 1;
	result = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		result = (str[i] - '0') + (result * 10);
		i++;
	}
	return (result * minus);
}
