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
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_USAGE "Usage: ./philo number_of_philosopher time_to_die time_to_eat time_to_sleep [number_of_times]"

typedef struct s_mtx
{
	int		index;

}			t_mtx;

typedef struct s_fork
{
	t_mtx	fork;
	int		id;
	int		thread_id;
}			t_fork;

typedef struct s_philo
{
	int		id;
	int		*left_fork;
	int		*right_fork;
	int		meals;
	bool	full;
	long	last_time;
	t_mtx	*mutexes;
}			t_philo;

typedef struct s_table
{
	int		nums;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	int		meals;
}			t_table;

int			ft_atoi(const char *str, int *error);
int			ft_strlen(char *str);

#endif