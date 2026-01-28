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

// int     create_thread(pthread_t *thread,)

// typedef struct s_mtx
// {
// 	int		index;

// }			t_mtx;

// typedef struct s_fork
// {
// 	t_mtx	fork;
// 	int		id;
// 	int		thread_id;
// }			t_fork;

// typedef struct s_philo
// {
// 	int		id;
// 	int		*left_fork;
// 	int		*right_fork;
// 	int		meals;
// 	bool	full;
// 	long	last_time;
// 	t_mtx	*mutexes;
// }			t_philo;

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

int	main(int ac, char **av)
{
	int		i;
	int		error;
	t_table	t;

	if (ac < 6 || !check_brackets(av[5]))
		return (print_usage());
	i = 1;
	error = 0;
	t.nums = ft_atoi(av[1], &error);
	t.t_die = ft_atoi(av[2], &error);
	t.t_eat = ft_atoi(av[3], &error);
	t.t_sleep = ft_atoi(av[4], &error);
	t.meals = ft_atoi(dup_digit(av[5]), &error);
	if (error)
		return (1);
	return (0);
}
