/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 15:35:17 by jaeshin           #+#    #+#             */
/*   Updated: 2023/10/01 15:36:19 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_thread(t_total *total)
{
	int	i;

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
	pthread_mutex_destroy(&total->args->action);
	pthread_mutex_destroy(&total->args->print);
}
