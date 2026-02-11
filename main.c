/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:46 by chitoupa          #+#    #+#             */
/*   Updated: 2026/01/28 14:17:09 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int pthread_create(pthread_t *restrict thread,
//        const pthread_attr_t *restrict attr,
//        void *(*start_routine)(void *),
//        void *restrict arg);

// typedef	struct s_mtx
// {
// 	pthread_mutex_t	l_fork;
// 	pthread_mutex_t	r_fork;
// }						t_mtx;

// typedef struct s_fork
// {
// 	t_mtx fork;
// 	int	fork_id;
// }				t_fork;

// typedef	struct	s_philo
// {
// 	int	id; //1..N
// 	int count;
// 	t_fork	*l_fork;
// 	t_fork	*r_fork;
// 	long long last_meal_time;
// 	pthread_t	thread_id;
// 	t_table	*table;
// }				t_philo;

// typedef struct s_table
// {
// 	int philo_num;
// 	int time_to_die;
// 	int	time_to_eat;
// 	int	time_to_sleep;
// 	int meal_num; //FLAG if -1
// 	long long start_time;
// 	pthread_mutex_t	dead_mutex;
// 	t_fork	*forks;
// 	t_philo	*philos;
// }				t_table;

pthread_t	*init_threads(int nums)
{
	int		id;
	t_philo	p;
	int		i;

	i = 0;
	while (i < nums)
	{
		p.id = i + 1;
	}
}

static int	print_usage(void)
{
	write(1, ERR_USAGE, 2);
}

static int	check_brakets(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[0] != '[' || str[len - 1] != ']')
		return (0);
	return (1);
}

static char	*dup_digit(char *str)
{
	char	*dup;
	int		len;
	int		i;

	len = ft_strlen(str) - 1;
	dup = (char *)malloc(sizeof(char) * len);
	if (!dup)
		return (NULL);
	i = 0;
	str++;
	while (i < len)
	{
		dup[i++] = *str;
		str++;
	}
	return (dup);
}

int	init_data(char av, t_table t)
{
	int error;

	error = 0;
	

}

int	main(int ac, char **av)
{
	int		i;
	int		error;
	t_table	t;

	if (ac != 5 || ac != 6 || !check_brackets(av[5]))
		return (print_usage());
	i = 1;
	error = 0;
	
	if (error)
		return (1);
	return (0);
}

// dinner_start
// end with no leak -> philos full | | 1 philo died
