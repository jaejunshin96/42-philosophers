/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:26:20 by jaeshin           #+#    #+#             */
/*   Updated: 2023/10/01 15:36:15 by jaeshin          ###   ########.fr       */
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

int	philo_eat(t_philo *p)
{
	if (pthread_mutex_lock(&p->args->forks[p->r_fork].mutex))
		return (0);
	if (pthread_mutex_lock(&p->args->forks[p->l_fork].mutex))
		return (0);
	print_action(p, p->args->start_time, FORK);
	print_action(p, p->args->start_time, FORK);
	print_action(p, p->args->start_time, EAT);
	ft_usleep(p->args->time_to_eat);
	p->count_of_eat++;
	return (1);
}

void	philo_sleep(t_philo *p)
{
	print_action(p, p->args->start_time, SLEEP);
	pthread_mutex_unlock(&p->args->forks[p->r_fork].mutex);
	pthread_mutex_unlock(&p->args->forks[p->l_fork].mutex);
	ft_usleep(p->args->time_to_sleep);
}

void	philo_think(t_philo *p)
{
	print_action(p, p->args->start_time, THINK);
}

void	*thread_func(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	if (p->id % 2 == 0)
		usleep(10);
	while (p->flag)
	{
		if (!philo_eat(p))
			continue;
		philo_sleep(p);
		philo_think(p);
	}
	return (NULL);
}

void	create_run_thread(t_total *total)
{
	int	i;

	i = -1;
	while (++i < total->args->nbr_of_phil)
	{
		pthread_create(&total->philos[i].thread,\
		 NULL, thread_func, &total->philos[i]);
		usleep(10);
	}
}

int	main(int argc, char **argv)
{
	t_total		*total;

	total = init_total(argc, argv);
	init_err(total);
	create_run_thread(total);
	join_thread(total);
	destroy_mutex(total);
	return (0);
}
