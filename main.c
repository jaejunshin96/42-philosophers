/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:26:20 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/20 18:14:26 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philo(void)
{
	t_philo	*philo;
	
	philo = (t_philo *)malloc(sizeof(t_philo) * 100);
	if (philo == NULL)
	{
		perror("init philo");
		exit(1);
	}
	philo->time_to_die = 100;
	philo->time_to_eat = 20;
	philo->time_to_sleep = 20;
	return (philo);
}

void	*print_random(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	printf("to die - %d\n", philo->time_to_die);
	philo->time_to_die -= 50;
	// printf("to die - %d\n", philo->to_die);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	pthread_t	thread;

	(void)argc;
	(void)argv;
	printf("here\n");
	philo = init_philo();
	// usleep(10000);
	pthread_create(&thread, NULL, print_random, NULL);
	printf("here1\n");
	// pthread_join(thread, NULL);
	return (0);
}
