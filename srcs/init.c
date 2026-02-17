/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:24:34 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/17 22:05:46 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *p, t_fork *f, int pos)
{
	int	n;

	n = p->table->philo_num;
	if (p->id % 2 == 1)
	{
		p->first_f = &f[pos];
		p->second_f = &f[(pos + 1) % n];
	}
	else
	{
		p->first_f = &f[(pos + 1) % n];
		p->second_f = &f[pos];
	}
}

static t_philo	*init_philo(t_table *t)
{
	t_philo *p;
	int i;

	t->philos = malloc(t->philo_num * sizeof(t_philo));
	if (!t->philos)
		return (cleanup_table(t, 0), NULL);
	p = t->philos;
	i = -1;
	while (++i < t->philo_num)
	{
		if (!safe_mutex_handle(&p[i].philo_mutex, INIT))
			return (0);
		p[i].id = i + 1;
		p[i].is_full = 0;
		p[i].meals_eaten = 0;
		p[i].table = t;
		p[i].last_meal_time = 0;
		assign_forks(p, t->forks, i);
	}
	return (p);
}

static t_fork *init_fork(t_table *t)
{
	t_fork *f;
	int i;

	t->forks = malloc(t->philo_num * sizeof(t_fork));
	if (!t->forks)
		return (cleanup_table(t, 0), NULL);
	f = t->forks;
	i = -1;
	while (++i < t->philo_num)
	{
		if (!safe_mutex_handle(&f[i].mutex, INIT))
			return (cleanup_table(t, i), NULL);
		f[i].id = i;
		f[i].taken = 0;
	}
	return (f);
}

void	parse_arg(t_table *t, int ac, char **av)
{
	int	i;
	int	res;
	int of;

	i = 0;
	res = 0;
	of = 0;
	while (++i < ac)
	{
		res = ft_atoi(av[i], &of);
		if (i == 1)
			t->philo_num = res;
		if (i == 2)
			t->t_die = res;
		if (i == 3)
			t->t_eat = res;
		if (i == 4)
			t->t_sleep = res;
		if (ac == 5)
			t->meal_num = -1;
		else if (i == 5)
			t->meal_num = res;
	}
}

t_table *init_table(int ac, char **av)
{
	t_table *t;

	t = malloc(sizeof(t_table) * 1);
	if (!t)
		return (NULL);
	parse_arg(t, ac, av);
	t->forks = NULL;
	t->philos = NULL;
	t->end = 0;
	t->threads_ready = 0;
	if (!safe_mutex_handle(&t->table_mutex, INIT)
		|| !safe_mutex_handle(&t->end_mutex, INIT)
		|| !safe_mutex_handle(&t->print_mutex, INIT))
		return (NULL);
	t->forks = init_fork(t);
	if (!t->forks)
		return (cleanup_table(t, t->philo_num), NULL);
	t->philos = init_philo(t);
	if (!t->philos)
		return (cleanup_table(t, t->philo_num), NULL);
	return (t);
}
