/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:46 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/11 23:48:45 by chitoupa         ###   ########.fr       */
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
// 	int t_die;
// 	int	t_eat;
// 	int	t_sleep;
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

static int	is_valide_input(char *str)
{
	char	*buff;
	int	len;
	int	i;

	len = ft_strlen(str);
	if (str[0] != '[' || str[len - 1] != ']')
		return (0);
	buff = malloc(len - 1);
	if (!buff)
		return (0);
	i = 1;
	while (i < len - 1)
	{
		buff[i - 1] = str[i];
		i++;
	}
	buff[i - 1] = '\0';
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

t_philo *init_philos(int num)
{
	t_philo *p;

	p = malloc(sizeof(t_philo) * num);
	if (!p)
		return (NULL);
	return (p);
}

t_fork *init_forks(int num)
{
	t_fork *f;

	f = malloc(sizeof(t_fork) * num);
	if (!f)
		return (NULL);
	return (f);
}

int	init_data(t_table *t, int ac, char **av)
{
	int error;

	error = 0;
	t->philo_num = ft_atoi(av[1], &error);
	t->t_die = ft_atoi(av[2], &error);
	t->t_eat = ft_atoi(av[3], &error);
	t->t_sleep = ft_atoi(av[4], &error);
	if (ac == 6 && check_brakets(av[5]))
		t->meal_num = ft_atoi(av[5], &error);
	else
		t->meal_num = -1;
	t->start_time = get_current_time();



}

int	main(int ac, char **av)
{
	int		i;
	int		error;
	t_table	t;

	if (ac != 5 || ac != 6 || !check_brackets(av[5]))
		return (print_usage());
	i = 1;
	if (!init_data(&t, ac, av))
		return (1);
	return (0);
}

// dinner_start
// end with no leak -> philos full | | 1 philo died
