/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:26:20 by jaeshin           #+#    #+#             */
/*   Updated: 2023/10/03 22:29:12 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat_count(t_philo *p)
{
	if (p->args->nbr_of_must_eat > 0 && \
		p->count_of_eat >= p->args->nbr_of_must_eat)
	{
		p->flag = 0;
		return (0);
	}
	return (1);
}

int	philo_eat(t_philo *p)
{
	if (!p->flag || !check_eat_count(p))
		return (0);
	if (!p->flag || pthread_mutex_lock(&p->args->forks[p->r_fork].mutex))
		return (0);
	if (!p->flag || pthread_mutex_lock(&p->args->forks[p->l_fork].mutex))
		return (0);
	print_action(p, p->args->start_time, FORK);
	print_action(p, p->args->start_time, FORK);
	print_action(p, p->args->start_time, EAT);
	p->last_meal = get_time();
	ft_usleep(p->args->time_to_eat);
	p->count_of_eat++;
	return (1);
}

void	philo_sleep(t_philo *p)
{
	if (p->flag)
	{
		print_action(p, p->args->start_time, SLEEP);
		pthread_mutex_unlock(&p->args->forks[p->r_fork].mutex);
		pthread_mutex_unlock(&p->args->forks[p->l_fork].mutex);
		ft_usleep(p->args->time_to_sleep);
	}
}

void	philo_think(t_philo *p)
{
	if (p->flag)
		print_action(p, p->args->start_time, THINK);
}

void	*thread_func(void *philo)
{
	t_philo	*p;

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
	pthread_mutex_unlock(&p->args->forks[p->r_fork].mutex);
	pthread_mutex_unlock(&p->args->forks[p->l_fork].mutex);
	return (NULL);
}

void	*watcher(void *philos)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)philos;
	i = -1;
	while (p->flag && ++i < p->args->nbr_of_phil)
	{
		if (p->args->time_to_die <= (get_time() - p[i].last_meal))
		{
			print_action(&p[i], p->args->start_time, DIE);
			i = -1;
			while (++i < p->args->nbr_of_phil)
				p[i].flag = 0;
			break;
		}
		if (i + 1 == p->args->nbr_of_phil)
			i = -1;
	}
	return (NULL);
}

void	create_run_thread(t_total *total)
{
	pthread_t	observer;
	int			i;

	pthread_create(&observer, NULL, watcher, total->philos);
	i = -1;
	while (++i < total->args->nbr_of_phil)
	{
		pthread_create(&total->philos[i].thread,\
		 NULL, thread_func, &total->philos[i]);
		usleep(10);
	}
	pthread_join(observer, NULL);
	i = -1;
	while (++i < total->args->nbr_of_phil)
		pthread_join(total->philos[i].thread, NULL);
}

void	print_if_all_eaten(t_total *total)
{
	int	i;

	i = -1;
	while (total->args->nbr_of_must_eat > 0 && \
		++i < total->philos->args->nbr_of_phil)
	{
		if (total->philos[i].count_of_eat < total->args->nbr_of_must_eat)
			break;
		if (i + 1 == total->args->nbr_of_phil)
			printf("Everyone has eaten %d times.\n", \
				total->args->nbr_of_must_eat);
	}
}

int	main(int argc, char **argv)
{
	t_total		*total;

	total = init_total(argc, argv);
	init_err(total);
	create_run_thread(total);
	destroy_mutex(total);
	print_if_all_eaten(total);
	return (0);
}
