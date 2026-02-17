/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:24:05 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/17 19:11:12 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *str, char *detail, int ret)
{
	if (!detail)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, detail);
	return (ret);
}

int	destroy_mutexes(t_table *t, int forks_inited)
{
	int i;

	if (!t)
		return (0);
	i = -1;
	while (++i < forks_inited)
	{
		if (!safe_mutex_handle(&t->forks[i].mutex, DESTROY))
			return (0);
	}
	i = -1;
	while (++i < t->philo_num)
	{
		if (!safe_mutex_handle(&t->philos[i].philo_mutex, DESTROY))
			return (0);
	}
	if (!safe_mutex_handle(&t->end_mutex, DESTROY))
		return (0);
	if (!safe_mutex_handle(&t->table_mutex, DESTROY))
		return (0);
	if (!safe_mutex_handle(&t->print_mutex, DESTROY))
		return (0);
	return (1);
}

void 	cleanup_table(t_table *t, int forks_inited)
{
	if (!t)
		return ;
	if (!destroy_mutexes(t, forks_inited))
		return ;
	if (t->forks)
	{
		free(t->forks);
		t->forks = NULL;
	}
	if (t->philos)
	{
		free(t->philos);
		t->philos = NULL;
	}
}

