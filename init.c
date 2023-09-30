/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:52:39 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/30 17:45:25 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_init(&args->action, NULL);
	pthread_mutex_init(&args->print, NULL);
	return (args);
}

t_fork	*init_fork(t_args *args)
{
	t_fork		*fork;
	int			i;

	fork = (t_fork *)malloc(sizeof(t_fork) * args->nbr_of_phil);
	if (fork == NULL)
		return (NULL);
	i = 0;
	while (i < args->nbr_of_phil)
	{
		fork[i].id = i + 1;
		pthread_mutex_init(&fork[i].mutex, NULL);
		i++;
	}
	args->forks = fork;
	return (fork);
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
		philo[i].flag = 1;
		philo[i].r_fork = i;
		if (i + 1 < args->nbr_of_phil)
			philo[i].l_fork = i + 1;
		else
			philo[i].l_fork = 0;
		philo[i].args = args;
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
	total->forks = init_fork(total->args);
	if (total->forks == NULL)
		return (NULL);
	total->philos = init_philo(total->args);
	if (total->philos == NULL)
		return (NULL);
	return (total);
}
