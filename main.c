/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:26:20 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/28 22:06:20 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		printf("get time erorr\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*thread_function(void *p)
{
	t_philo		*philo;
	long long	time;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->args->active);
	time = get_time();
	printf("%lldms philo %d\n",time - philo->args->start_time , philo->id);
	pthread_mutex_lock(&philo->args->forks[philo->r_fork].mutex);
	pthread_mutex_lock(&philo->args->forks[philo->l_fork].mutex);
	time = get_time();
	printf("%lldms philo %d has taken a fork.\n",time - philo->args->start_time , philo->id);
	printf("%lldms philo %d has taken a fork.\n",time - philo->args->start_time , philo->id);
	pthread_mutex_unlock(&philo->args->forks[philo->r_fork].mutex);
	pthread_mutex_unlock(&philo->args->forks[philo->l_fork].mutex);
	pthread_mutex_unlock(&philo->args->active);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_total		*total;
	pthread_t	thread;
	int			i;

	total = init_total(argc, argv);
	init_err(total);
	i = 0;
	total->args->start_time = get_time();
	while (i < total->args->nbr_of_phil)
	{
		if (pthread_create(&thread, NULL, thread_function, &total->philos[i]) != 0)
			printf("pthread create error\n");
		usleep(1);
		if (pthread_detach(thread) != 0)
			printf("detach error\n");
		i++;
	}
	return (0);
}
