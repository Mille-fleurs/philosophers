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

static int	init_fork(t_table *t, int *forks_inited)
{
	int i;

	*forks_inited = 0;
	t->forks = malloc(t->philo_num * sizeof(t_fork));
	if (!t->forks)
		return (0);
	i = -1;
	while (++i < t->philo_num)
	{
		if (!safe_mutex_handle(&t->forks[i].mutex, INIT))
		{
			*forks_inited = i;
			return (0);
		}
		t->forks[i].id= i;
	}
	*forks_inited = t->philo_num;
	return (1);
}

static int	init_philo(t_table *t, int *philos_inited)
{
	int i;

	*philos_inited = 0;
	t->philos = malloc(t->philo_num * sizeof(t_philo));
	if (!t->philos)
		return (0);
	i = -1;
	while (++i < t->philo_num)
	{
		if (!safe_mutex_handle(&t->philos[i].philo_mutex, INIT))
		{
			*philos_inited = i;
			return (0);
		}
		t->philos[i].id = i + 1;
		t->philos[i].is_full = 0;
		t->philos[i].meals_eaten = 0;
		t->philos[i].table = t;
		t->philos[i].last_meal_time = 0;
		assign_forks(&t->philos[i], t->forks, i);
	}
	*philos_inited = t->philo_num;
	return (1);
}

static int	init_table_mutexes(t_table *t)
{
	if (!safe_mutex_handle(&t->table_mutex, INIT))
		return (0);
	t->table_inited = 1;
	if (!safe_mutex_handle(&t->end_mutex, INIT))
	{
		if (t->table_inited)
			safe_mutex_handle(&t->table_mutex, DESTROY);
		return (0);
	}
	t->end_inited = 1;
	if (!safe_mutex_handle(&t->print_mutex, INIT))
	{
		if (t->end_inited)
			safe_mutex_handle(&t->end_mutex, DESTROY);
		if (t->table_inited)
			safe_mutex_handle(&t->table_mutex, DESTROY);
		return (0);
	}
	t->print_inited = 1;
	return (1);
}

t_table *init_table(int ac, char **av)
{
	t_table *t;
	int	forks_inited;
	int	philos_inited;

	forks_inited = 0;
	philos_inited = 0;
	t = malloc(sizeof(*t));
	if (!t)
		return (NULL);
	memset(t, 0, sizeof(*t));
	if (!parse_arg(t, ac, av))
		return (free(t), NULL);
	if (!init_table_mutexes(t))
		return (cleanup_table(t, 0, 0), NULL);
	if (!init_fork(t, &forks_inited))
		return (cleanup_table(t, forks_inited, 0), NULL);
	if (!init_philo(t, &philos_inited))
		return (cleanup_table(t, forks_inited, philos_inited), NULL);
	return (t);
}

