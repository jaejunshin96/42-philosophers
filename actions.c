/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:53:47 by jaeshin           #+#    #+#             */
/*   Updated: 2023/10/04 10:54:52 by jaeshin          ###   ########.fr       */
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
	if (p->flag)
	{
		print_action(p, p->args->start_time, FORK);
		print_action(p, p->args->start_time, FORK);
		print_action(p, p->args->start_time, EAT);
		p->last_meal = get_time();
		ft_usleep(p->args->time_to_eat);
		p->count_of_eat++;
	}
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
