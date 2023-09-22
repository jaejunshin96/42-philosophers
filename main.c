/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:26:20 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/22 17:25:54 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philo(void)
{
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
	{
		perror("init philo");
		exit(1);
	}
	pthread_mutex_init(&philo->mutex, NULL);
	philo->time_to_die = 100;
	philo->time_to_eat = 20;
	philo->time_to_sleep = 20;
	return (philo);
}

void	*death_timer(void *p)
{
	t_philo		*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->mutex);
	printf("thread 1 to die - %d\n", philo->time_to_die);
	philo->time_to_die -= 50;
	pthread_mutex_unlock(&philo->mutex);
	return (NULL);
}

void	*death_timer2(void *p)
{
	t_philo		*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->mutex);
	printf("thread 2 to die - %d\n", philo->time_to_die);
	philo->time_to_die -= 20;
	pthread_mutex_unlock(&philo->mutex);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_t		thread;
	pthread_t		thread2;
	struct timeval	tv;

	(void)argc;
	(void)argv;
	philo = init_philo();
	gettimeofday(&tv, NULL);
	printf("tv sec - %lld ms\n",(long long) tv.tv_sec * 1000 + tv.tv_usec / 1000);
	pthread_create(&thread, NULL, death_timer, (void *)philo);
	usleep(1);
	pthread_create(&thread2, NULL, death_timer2, (void *)philo);
	pthread_join(thread, NULL);
	pthread_join(thread2, NULL);
	pthread_mutex_destroy(&philo->mutex);
	printf("time to die - %d\n", philo->time_to_die);
	return (0);
}
