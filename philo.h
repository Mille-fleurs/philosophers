/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:41 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/15 21:07:16 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_h

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define ERR_USAGE "Usage: ./philo number_of_philosopher time_to_die time_to_eat time_to_sleep [number_of_times]"

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t		mtx;
	int					id;
	int					taken;
}						t_fork;

typedef struct s_philo
{
	int id; // 1..N
	int					is_full;
	int					meals_eaten;
	int					f_num;
	t_fork				*first_f;
	t_fork				*second_f;
	long long			last_meal_time;
	pthread_t			thread_id;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					philo_num;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int 				meal_num; // FLAG if -1, number of time each philos must eat
	int 				end;      // someone died or ate enough(all philos eaten their meal_num)
	int					threads_ready;
	long long			start_time;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		end_mutex;
	pthread_t			monitor;
	t_fork				*forks;
	t_philo				*philos;
}						t_table;

typedef enum s_op
{
	LOCK,
	UNLOCK,
	CREATE,
	INIT,
	DESTROY,
	JOIN,
	DETACH,
}						t_op;

typedef enum s_status
{
	EATING,
	SLEEPING,
	THINKING,
	GOT_FORK_1,
	GOT_FORK_2,
	DIED
}						t_status;

void					*philosopher(void *data);
int						error_msg(char *str);
void					handle_thread_error(int status, t_op op);
int						safe_thread_handle(pthread_t *t,
							void *(*routine)(void *), void *arg, t_op op);
void					handle_mutex_error(int status, t_op op);
int						safe_thread_handle(pthread_t *t,
							void *(*routine)(void *), void *arg, t_op op);
int						set_int(pthread_mutex_t *mtx, int *dest, int value);
int						get_int(pthread_mutex_t *mtx, int *value);
int						set_long_long(pthread_mutex_t *mtx, long long *dest,
							long long value);
int						get_long_log(pthread_mutex_t *mtx, long long *value);
void					cleanup_table(t_table *t, int forks_inited);
int						ft_atoi(const char *str, int *error);
int						ft_strlen(char *str);
size_t					get_current_time(void);

#endif