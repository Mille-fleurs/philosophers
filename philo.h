/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:41 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/14 19:29:37 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_h

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define ERR_USAGE "Usage: ./philo number_of_philosopher time_to_die time_to_eat time_to_sleep [number_of_times]"

typedef struct s_table t_table;

typedef struct s_fork
{
	pthread_mutex_t mtx;
	int	id;
	int taken;
}				t_fork;

typedef	struct	s_philo
{
	int	id; //1..N
	int is_full;
	int	meals_eaten;
	t_fork	*first_f;
	t_fork	*second_f;
	long long last_meal_time;
	pthread_t	thread_id;
	t_table	*table;
}				t_philo;

typedef struct s_table
{
	int philo_num;
	int t_die;
	int	t_eat;
	int	t_sleep;
	int meal_num; //FLAG if -1
	int	end; //someone died or ate enoughS
	int all_thread_ready;
	long long start_time;
	pthread_mutex_t table_mutex;
	pthread_mutex_t	end_mutex;
	t_fork	*forks;
	t_philo	*philos;
}				t_table;

typedef enum s_op
{
	LOCK,
	UNLOCK,
	CREATE,
	INIT,
	DESTROY,
	JOIN,
	DETACH,
}			t_op;

typedef enum s_status
{
	EAT,
	SLEEP,
	THINK,
	LEFT_FORK,
	RIGHT_FORK,
	DIED
}			t_status;

void     cleanup_table(t_table *t, int forks_inited, int end_inited);
int			ft_atoi(const char *str, int *error);
int			ft_strlen(char *str);

#endif