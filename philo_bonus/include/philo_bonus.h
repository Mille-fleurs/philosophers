/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:45:58 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/24 20:39:55 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

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
# define STR_ERR_PTHREAD "%s error: Could not create thread.\n"
# define STR_ERR_MALLOC "%s error: Could not allocate memory.\n"
# define STR_ERR_GETTIME "%s error: Could not get current time.\n"
# define STR_ERR_SEM "%s error: Could not create semaphore.\n"
# define STR_ERR_FORK "%s error: Could not fork child.\n"

# define SEM_FORKS "/philo_global_forks"
# define SEM_PRINT "/philo_global_print"
# define SEM_FULL "/philo_global_full"
# define SEM_DEAD "/philo_global_dead"
# define SEM_STOP "/philo_global_stop"
# define SEM_MEAL "/philo_local_meal_"

# define CHILD_EXIt_ERR_PTHREAD 40
# define CHILD_EXIT_ERR_SEM 41
# define CHILD_EXIT_PHILO_FULL 42
# define CHILD_EXIT_PHILO_DEAD 43

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			personal_monitor;
	sem_t				*sem_forks;
	sem_t				*sem_print;
	sem_t				*sem_philo_full;
	sem_t				*sem_philo_dead;
	sem_t				*sem_meal;
	char				*sem_meal_name;
	unsigned int		id;
	int					meals_eaten;
	int					is_full;
	long				last_meal_time;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	unsigned int		philo_num;
	long				start_time;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meal_num;
	sem_t				*sem_forks;
	sem_t				*sem_print;
	sem_t				*sem_stop;
	sem_t				*sem_philo_full;
	sem_t				*sem_philo_dead;
	int					sim_stop;
	pid_t				*pids;
	pthread_t			meal_monitor;
	pthread_t			death_monitor;
	t_philo				**philos;
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

int						is_valid_arg(int ac, char **av);
int						parse_arg(t_table *t, int ac, char **av);
t_table 				*init_table(int ac, char **av);
void    				*philosopher(void *data);
void					*personal_monitor(void *data);
void    				*meal_monitor(void *data);
void    				*death_monitor(void *data);
void					print_status(t_philo *philo, t_status code);
time_t					get_current_time(void);
void					precise_sleep(long ms);
int    					kill_philos(t_table *t, int exit_code);
void					*free_table(t_table *t);
void					unlink_global_sems(void);
int						sem_error_cleanup(t_table *t);
int						cleanup_table(t_table *t, int exit_code);
int						error_msg(char *str, char *detail, int ret);
int						error_failure(char *s, char *details, t_table *t, int child_id);
int 					sem_failure(t_table *t, int ret);
void					*init_failure_exit(t_table *t);
int						ft_strlen(char *str);
char					*ft_strcat(char *dest, char *src);
char					*ft_utoa(unsigned int n);

#endif