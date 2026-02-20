/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 20:31:18 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/20 21:49:48 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include<stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

# define MAX_PHILO 250
# define STR_MAX_PHILO "250"
# define STR_PROG_NAME "philo:"
# define STR_USAGE \
	"%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT \
	"%s invalid input: %s: \
not a valid unsigned integer between 0 and 2147483647.\n"
# define STR_ERR_INPUT_POFLOW \
	"%s invalid input: \
there must be between 1 and %s philosophers.\n"
# define STR_ERR_MALLOC "%s error: Could not allocate memory.\n"
# define STR_ERR_GETTIME "%s error: Could not get current time.\n"
# define STR_ERR_SEM     "%s error: Could not create semaphore.\n"
# define STR_ERR_FORK    "%s error: Could not fork child.\n"

# define CHILD_EXIt_ERR_PTHREAD 40
# define CHILD_EXIT_ERR_SEM     41
# define CHILD_EXIT_PHILO_FULL  42
# define CHILD_EXIT_PHILO_DEAD  43

typedef struct s_philo
{
	pid_t				pid;
	int 				id;
	int					meals_eaten;
	long				last_meal_time;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					philo_num;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int 				meal_num;
	
	sem_t				*sem_forks;
	sem_t 				*sem_print;
	sem_t 				*sem_stop;
	sem_t 				*sem_philo_full;
	sem_t				*sem_philo_dead;
	sem_t				*sem_meal;
	pthread_t			gluttony_monitor;
	pthread_t			famine_monitor;
	t_philo				*philos;
}						t_table;

typedef enum s_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}						t_status;

void					*philosopher(void *data);
int						preparation(t_table *t);
int						wait_until_ready(t_table *t);
void					only_one_philo(t_table *t);
void					end_on_error(t_table *t);
int						unlock_forks_return(t_philo *p, int must_set);
int						unlock_forks_end(t_philo *p, int must_set);
void					print_status(t_table *t, int p_index, t_status code);
void					*monitor(void *data);
int						is_valid_arg(int ac, char **av);
int						parse_arg(t_table *t, int ac, char **av);
t_table					*init_table(int ac, char **av);
void					handle_mutex_error(int status, t_op op);
int						safe_mutex_handle(pthread_mutex_t *mtx, t_op code);
void					handle_thread_error(int status, t_op op);
int						safe_thread_handle(pthread_t *t,
							void *(*routine)(void *), void *arg, t_op op);
int						set_int(pthread_mutex_t *mtx, int *dest, int value);
int						get_int(pthread_mutex_t *mtx, int *value);
int						set_long(pthread_mutex_t *mtx, long *dest, long value);
long					get_long(pthread_mutex_t *mtx, long *value);
int						simulation_finished(t_table *t);
void					cleanup_table(t_table *t, int forks_inited, int philo_inited);
int						error_msg(char *str, char *detail, int ret);
int						ft_strlen(char *str);
long					get_current_time(void);
void					precise_sleep(t_table *t, long ms);

#endif