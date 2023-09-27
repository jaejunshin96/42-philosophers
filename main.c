/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:26:20 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/27 16:34:49 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// convert tv_sec to milliseconds by multiplying 1000
// convert tv_usec to milliseconds by dividing 1000
long long	get_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		printf("get time erorr\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	main(int argc, char **argv)
{
	t_total	*total;
	int		i; 

	total = init_total(argc, argv);
	init_err(total);
	i = 0;
	while (i < total->args->nbr_of_phil)
	{
		printf("Philosopher %d", total->philos[i].id);
		printf(" args - %d, %d, %d\n", total->philos[i].args->time_to_die, total->philos[i].args->time_to_eat, total->philos[i].args->time_to_sleep);
		i++;
	}
	return (0);
}
