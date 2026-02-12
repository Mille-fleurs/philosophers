/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:41 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/11 21:42:21 by chitoupa         ###   ########.fr       */
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

typedef	struct s_mtx
{
	pthread_mutex_t	fork;
	int	index;
}						t_mtx;

typedef struct s_fork
{
	t_mtx fork;
	int	fork_id;
}				t_fork;

typedef	struct	s_philo
{
	int	id; //1..N
	int count;
	t_fork	*l_fork;
	t_fork	*r_fork;
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
	long long start_time;
	pthread_mutex_t	dead_mutex;
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
	DETATCH,
}			t_op;

// typedef struct 	s_philo
// {
// 	pthread_t		thread;
// 	int				id;
// 	int 			eating;
// 	int				meals_eaten;
// 	size_t			last_meal; /* current_time - last_meal > time_to_die */
// 	size_t			time_to_die;
// 	size_t			time_to_eat;
// 	size_t			time_to_sleep;
// 	size_t			start_time;
// 	int				num_philos;
// 	int				num_times_eat;
// 	int				*dead;
// 	pthread_mutex_t	*r_fork;
// 	pthread_mutex_t *l_fork;
// 	pthread_mutex_t	*write_lock;
// 	pthread_mutex_t *dead_lock;
// 	pthread_mutex_t *meal_lock;
// }				t_philo;

// typedef struct	s_program
// {
// 	int				dead_flag;
// 	pthread_mutex_t	dead_lock;
// 	pthread_mutex_t meal_lock;
// 	pthread_mutex_t	write_lock;
// 	t_philo			*philos;
// }				t_program;

int			ft_atoi(const char *str, int *error);
int			ft_strlen(char *str);

#endif