/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:26:20 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/26 15:45:02 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// convert tv_sec to milliseconds by multiplying 1000
// convert tv_usec to milliseconds by dividing 1000
long long	get_time(void)
{
	struct timeval current_time;

	if (gettimeofday(&current_time, NULL) == 0)
		return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	else
		printf("time error\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_total	*total;
	int		i;

	total = init_total(argc, argv);
	init_err(total);
	i = 0;
	long long	time_a = get_time();
	usleep(2000);
	long long	time_b = get_time();
	printf("time diff - %lld\n", time_b - time_a);
	while (i < total->args->nbr_of_phil)
	{
		printf("Philosoper %d", total->philos[i].id);
		printf(" right_c - %d left_c - %d\n", total->philos[i].r_chopstick, total->philos[i].l_chopstick);
		i++;
	}
	return (0);
}
