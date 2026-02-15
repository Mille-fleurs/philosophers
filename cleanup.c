/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:24:05 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/15 21:07:10 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_table(t_table *t, int forks_inited)
{
	int	i;

	if (!t)
		return ;
	if (t->philos)
		free(t->philos);
	if (!destroy_mutexes(t, forks_inited))
		return ;
	t->philos = NULL;
	t->forks = NULL;
}

int	destroy_mutexes(t_table *t, int forks_inited)
{
	int i;

	if (t->forks)
	{
		i = -1;
		while (++i < forks_inited)
		{
			if (!safe_mutex_handle(t->forks[i].mtx, DESTROY))
				return (cleanup_table(t, forks_inited), 0);
		}
		free(t->forks);
	}
	if (!safe_mutex_handle(&t->end_mutex) || !safe_mutex_handle(&t->table_mutex))
		return (cleanup_table(t, forks_inited), 0);
}
