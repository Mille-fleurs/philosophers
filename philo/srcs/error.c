/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:24:05 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/27 10:14:38 by chitoupa         ###   ########.fr       */
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

static void	destroy_mutexes(t_table *t, int forks_inited, int philo_inited)
{
	int	i;

	if (!t)
		return ;
	if (t->forks)
	{
		i = -1;
		while (++i < forks_inited)
			safe_mutex_handle(&t->forks[i].mutex, DESTROY);
	}
	if (t->philos)
	{
		i = -1;
		while (++i < philo_inited)
			safe_mutex_handle(&t->philos[i].philo_mutex, DESTROY);
	}
	if (t->end_inited)
		safe_mutex_handle(&t->end_mutex, DESTROY);
	if (t->table_inited)
		safe_mutex_handle(&t->table_mutex, DESTROY);
	if (t->print_inited)
		safe_mutex_handle(&t->print_mutex, DESTROY);
}

void	cleanup_table(t_table *t, int forks_inited, int philo_inited)
{
	if (!t)
		return ;
	destroy_mutexes(t, forks_inited, philo_inited);
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
	free(t);
}
