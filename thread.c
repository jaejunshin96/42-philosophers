/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 15:35:17 by jaeshin           #+#    #+#             */
/*   Updated: 2023/10/04 11:10:06 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_func(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->id % 2 == 0)
		usleep(10);
	if (p->args->nbr_of_phil == 1)
		return (NULL);
	while (p->flag)
	{
		if (!philo_eat(p))
			continue ;
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
			break ;
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
		pthread_create(&total->philos[i].thread, \
		NULL, thread_func, &total->philos[i]);
		usleep(10);
	}
	pthread_join(observer, NULL);
	i = -1;
	while (++i < total->args->nbr_of_phil)
		pthread_join(total->philos[i].thread, NULL);
}

void	destroy_mutex(t_total *total)
{
	int	i;

	i = -1;
	while (++i < total->args->nbr_of_phil)
		pthread_mutex_destroy(&(total->forks[i].mutex));
	pthread_mutex_destroy(&total->args->print);
}
