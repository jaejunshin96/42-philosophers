/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:26:20 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/29 17:54:54 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	print_state(t_philo *p, long long time, int state)
{
	if (state == EAT)
	{
		printf("%lldms philo %d has taken a fork.\n", time - p->args->start_time , p->id);
		printf("%lldms philo %d has taken a fork.\n", time - p->args->start_time , p->id);
		printf("%lldms philo %d is eating.\n", time - p->args->start_time , p->id);
	}
}
// todo - time is not adding up
void	eat(t_philo *philo)
{
	long long	time;

	time = get_time();
	pthread_mutex_lock(&philo->args->forks[philo->r_fork].mutex);
	pthread_mutex_lock(&philo->args->forks[philo->l_fork].mutex);
	print_state(philo, time, EAT);
	pthread_mutex_unlock(&philo->args->forks[philo->r_fork].mutex);
	pthread_mutex_unlock(&philo->args->forks[philo->l_fork].mutex);
	ft_usleep(philo->args->time_to_eat);
}

void	*thread_func(void *p)
{
	t_philo		*philo;

	philo = (t_philo *)p;
	eat(philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_total		*total;
	pthread_t	thread;
	int			i;

	total = init_total(argc, argv);
	init_err(total);
	i = -1;
	total->args->start_time = get_time();
	while (++i < total->args->nbr_of_phil)
	{
		//printf("thread loop goes first?\n");
		pthread_create(&thread, NULL, thread_func, &total->philos[i]);
		usleep(10);
		pthread_detach(thread);
	}
	i = -1;
	while (++i < total->args->nbr_of_phil)
		pthread_mutex_destroy(&(total->forks[i].mutex));
	return (0);
}
