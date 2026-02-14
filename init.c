/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:24:34 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/14 18:20:40 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		return (NULL);
	return (ret);
}

void	assign_forks(t_philo *p, t_fork *f, int pos)
{
	int n;

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

void	init_philo(t_table *t)
{
    int i;
    t_philo *p;

    i = -1;
    while (++i < t->philo_num)
    {
        p = &t->philos[i];
		p->id =  i + 1;
		p->is_full = 0;
		p->meals_eaten = 0;
		p->table = t;
		p->last_meal_time = t->start_time;
		assign_forks(p, t->forks, i);
    }
}

int parse_args(t_table *t, int ac, char **av)
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
	if (error)
		return (1);
	if (t->philo_num <= 0 || t->t_die <= 0 || t->t_eat <= 0 || t->t_sleep <= 0)
		return (1);
	if (ac == 6 && t->meal_num <= 0)
		return (1);
	return (0);
}

int	init_table(t_table *t, int ac, char **av)
{
    int i;

	t->forks = NULL;
	t->philos = NULL;
	t->end = 0;
	t->all_thread_ready = 0;
	if (parse_args(t, ac, av))
		return (1);
	t->start_time = get_current_time();
	if (safe_mutex_handle(t->table_mutex, INIT) || safe_mutex_handle(&t->end_mutex, INIT))
		return (1);
	t->forks = safe_malloc(t->philo_num * sizeof(t_fork));
	if (!t->forks)
		return (cleanup_table(t, 0, 1), 1);
	t->philos = safe_malloc(t->philo_num * sizeof(t_philo));
	if (!t->philos)
		return (cleanup_table(t, 0, 1), 1);
    i = -1;
    while (++i < t->philo_num)
    {
		t->forks[i].id = i;
        if (safe_mutex_handle(&t->forks[i], INIT))
			return (cleanup_table(t, i, 1), 1);
    }
	init_philo(t);
	return (0);
}
