/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:52:39 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/23 22:10:30 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_args	*init_args(int argc, char **argv)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	if (argc != 5 || argc != 6 || args == NULL)
		return (NULL);
	args->nbr_of_phil = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nbr_of_must_eat = ft_atoi(argv[5]);
	return (args);
}

t_philo	*init_philo(t_args *args)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)malloc(sizeof(t_philo) * args->nbr_of_phil);
	if (philo == NULL)
		return (NULL);
	i = 0;
	while (i < args->nbr_of_phil)
	{
		philo[i].id = i + 1;
		i++;
	}
	philo->count_of_eat = 0;
	return (philo);
}

t_chopstick	*init_chopstick(t_args *args)
{
	t_chopstick	*chopstick;
	int			i;

	chopstick = (t_chopstick *)malloc(sizeof(t_chopstick) * args->nbr_of_phil);
	if (chopstick == NULL)
		return (NULL);
	i = 0;
	while (i < args->nbr_of_phil)
	{
		chopstick[i].id = i + 1;
		pthread_mutex_init(&chopstick[i].mutex, NULL);
		i++;
	}
	return (chopstick);
}

t_total	*init_total(int argc, char **argv)
{
	t_total	*total;

	total = malloc(sizeof(t_total));
	if (total == NULL)
		return (NULL);
	total->args = init_args;
	if (total == NULL)
		return (NULL);
	total->philos = init_philo;
	if (total->philos == NULL)
		return (NULL);
	total->chopsticks =init_chopstick;
	if (total->chopsticks == NULL)
		return (NULL);
	return (total);
}
