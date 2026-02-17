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
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define ERR_USAGE "Usage: ./philo number_of_philosopher time_to_die time_to_eat time_to_sleep [number_of_times]"

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	int					id;
	int					taken;
}						t_fork;

typedef struct s_philo
{
	int 				id; // 1..N
	int					is_full;
	int					meals_eaten;
	t_fork				*first_f;
	t_fork				*second_f;
	long				last_meal_time;
	pthread_t			thread_id;
	pthread_mutex_t		philo_mutex;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					philo_num;
	long					t_die;
	int					t_eat;
	int					t_sleep;
	int 				meal_num; // FLAG if -1, number of time each philos must eat
	int 				end;      // someone died or ate enough(all philos eaten their meal_num)
	int					threads_ready;
	long				start_time;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		end_mutex;
	pthread_mutex_t		print_mutex;
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

int    					start_simulation(t_table *t);
int     				stop_simulation(t_table *t, int forks_inited);
void					only_one_philo(t_table *t);
void					*philosopher(void *data);
void					print_status(t_table *t, int p_index, t_status code);
void    				*monitor(void *data);
void					*safe_malloc(size_t bytes);
void					assign_forks(t_philo *p, t_fork *f, int pos);
int						init_philo(t_table *t, int index);
int						parse_args(t_table *t, int ac, char **av);
int						init_table(t_table *t, int ac, char **av);
void					handle_mutex_error(int status, t_op op);
int 					safe_mutex_handle(pthread_mutex_t *mtx, t_op code);
void					handle_thread_error(int status, t_op op);
int						safe_thread_handle(pthread_t *t, void *(*routine)(void *), void *arg, t_op op);
int						set_int(pthread_mutex_t *mtx, int *dest, int value);
int						get_int(pthread_mutex_t *mtx, int *value);
int						set_long(pthread_mutex_t *mtx, long *dest, long value);
long					get_long(pthread_mutex_t *mtx, long *value);
void					cleanup_table(t_table *t, int forks_inited);
int						error_msg(char *str);
int						ft_atoi(const char *str, int *error);
int						ft_strlen(char *str);
size_t					get_current_time(void);
int						ft_usleep(size_t milliseconds);

#endif