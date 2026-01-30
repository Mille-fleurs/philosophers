/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:41 by chitoupa          #+#    #+#             */
/*   Updated: 2026/01/28 14:17:11 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_h

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_USAGE "Usage: ./philo number_of_philosopher time_to_die time_to_eat time_to_sleep [number_of_times]"

typedef struct 	s_philo
{
	pthread_t		thread;
	int				id;
	int 			eating;
	int				meals_eaten;
	size_t			last_meal; /* current_time - last_meal > time_to_die */
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_philos;
	int				num_times_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *dead_lock;
	pthread_mutex_t *meal_lock;
}				t_philo;

typedef struct	s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}				t_program;

int			ft_atoi(const char *str, int *error);
int			ft_strlen(char *str);

#endif