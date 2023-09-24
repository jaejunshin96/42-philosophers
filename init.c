/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:52:39 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/24 13:03:06 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_args	*init_args(int argc, char **argv)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	if (args == NULL)
		return (NULL);
	args->nbr_of_phil = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nbr_of_must_eat = ft_atoi(argv[5]);
	return (args);
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
		philo[i].r_chopstick = i + 1;
		if (i + 1 < args->nbr_of_phil)
			philo[i].l_chopstick = i + 2;
		else
			philo[i].l_chopstick = 1;
		i++;
	}
	philo->count_of_eat = 0;
	return (philo);
}

t_total	*init_total(int argc, char **argv)
{
	t_total	*total;

	if (argc != 5 && argc != 6)
		return (NULL);
	total = malloc(sizeof(t_total));
	if (total == NULL)
		return (NULL);
	total->args = init_args(argc, argv);
	if (total->args == NULL)
		return (NULL);
	total->chopsticks = init_chopstick(total->args);
	if (total->chopsticks == NULL)
		return (NULL);
	total->philos = init_philo(total->args);
	if (total->philos == NULL)
		return (NULL);
	return (total);
}
