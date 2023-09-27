/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:46:06 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/27 14:20:50 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_fork {
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_args {
	int			nbr_of_phil;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nbr_of_must_eat;
	int			total_nbr_eat;
	long long	start_time;
}	t_args;

typedef struct s_philo {
	int		id;
	int		l_fork;
	int		r_fork;
	int		count_of_eat;
	t_args	*args;
}	t_philo;

typedef struct s_total {
	t_fork		*chopsticks;
	t_args		*args;
	t_philo		*philos;
}	t_total;

// INIT
t_args		*init_args(int argc, char **argv);
t_philo		*init_philo(t_args *args);
t_fork		*init_fork(t_args *args);
t_total		*init_total(int argc, char **argv);

// UTILES
int			ft_atoi(const char *str);

// ERROR
void		init_err(t_total *total);

#endif
