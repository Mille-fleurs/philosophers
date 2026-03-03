/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:45:58 by chitoupa          #+#    #+#             */
/*   Updated: 2026/03/03 14:18:11 by chitoupa         ###   ########.fr       */
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

# ifndef DEBUG
#  define DEBUG 0
# endif

# define MAX_PHILO 250
# define STR_MAX_PHILO "250"
# define STR_PROG_NAME "philo:"
# define STR_USAGE "%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT "%s invalid input: %s: \
not a valid unsigned integer between 0 and 2147483647.\n"
# define STR_ERR_INPUT_POFLOW "%s invalid input: \
number_of_philosophers must be between 1 and %s philosophers.\n"
# define STR_ERR_INPUT_POSITIVE "%s invalid input: %s must be greater than 0.\n"
# define STR_ERR_PTHREAD "%s error: Could not create thread.\n"
# define STR_ERR_MALLOC "%s error: Could not allocate memory.\n"
# define STR_ERR_GETTIME "%s error: Could not get current time.\n"
# define STR_ERR_SEM "%s error: Could not create semaphore.\n"
# define STR_ERR_FORK "%s error: Could not fork child.\n"

# define INIT_OK 1
# define INIT_ERR_MALLOC 0
# define INIT_ERR_SEM -1

# define SEM_FORKS "/philo_global_forks"
# define SEM_PRINT "/philo_global_print"
# define SEM_FULL "/philo_global_full"
# define SEM_DEAD "/philo_global_dead"
# define SEM_STOP "/philo_global_stop"
# define SEM_DEATH_LOCK "/philo_death_lock"
# define SEM_MEAL "/philo_local_meal_"

# define CHILD_EXIT_ERR_PTHREAD 40
# define CHILD_EXIT_ERR_SEM 41
# define CHILD_EXIT_PHILO_FULL 42
# define CHILD_EXIT_PHILO_DEAD 43

# define NC "\e[0m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define PURPLE "\e[35m"
# define CYAN "\e[36m"

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			personal_monitor;
	sem_t				*sem_forks;
	sem_t				*sem_print;
	sem_t				*sem_philo_full;
	sem_t				*sem_philo_dead;
	sem_t				*sem_death_lock;
	sem_t				*sem_meal;
	char				*sem_meal_name;
	unsigned int		id;
	int					meals_eaten;
	int					is_full;
	int					stop;
	int					exit_code;
	int					forks_held;
	long				last_meal_time;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					philo_num;
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
	sem_t				*sem_death_lock;
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
t_table					*init_table(int ac, char **av);
void					*philosopher(void *data);
void					*personal_monitor(void *data);
void					*meal_monitor(void *data);
void					*death_monitor(void *data);
void					print_status(t_philo *philo, t_status code);
void					debug_parent(t_table *t, const char *msg, int pid);
void					debug_monitor(t_table *t, const char *msg, int pid);
void					debug_philo(t_philo *p, const char *msg);
void					debug_exit_philo(t_philo *p);
void					debug_exit_parent(t_table *t, int pid, int status);
void					set_stop(t_philo *p, int code);
int						get_stop(t_philo *p);
int						take_forks(t_philo *p);
void					drop_forks(t_philo *p);
void					start_monitor(t_philo *p);
void					unblock_monitor_threads(t_table *t);
void					join_monitor_threads(t_table *t);
void					set_int(sem_t *lock, int *dest, int value);
int						get_int(sem_t *lock, int *src);
long					set_long(sem_t *lock, long *dest, long value);
long					get_long(sem_t *lock, long *src);
time_t					get_current_time(void);
void					precise_sleep(long ms);
void					kill_and_wait_children(t_table *t);
void					unlink_global_sems(void);
void					cleanup_table(t_table *t, int sem_opened,
							int children_created);
int						error_msg(char *str, char *detail, int ret);
int						error_exit(char *s, t_table *t, int sem_opened,
							int children_created);
t_table					*init_error(char *s, t_table *t, int sem_opened,
							int children_created);
int						ft_strlen(char *str);
char					*ft_strcat(char *dest, char *src);
char					*ft_utoa(unsigned int n);

#endif
