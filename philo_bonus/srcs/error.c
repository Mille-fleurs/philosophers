/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:24:05 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/20 21:54:55 by chitoupa         ###   ########.fr       */
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

static int	destroy_mutexes(t_table *t, int forks_inited, int philo_inited)
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
	while (++i < philo_inited)
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

void 	unlink_sems(t_table *t)
{
	sem_unlink(t->sem_forks);
	sem_unlink(t->sem_print);
	sem_unlink(t->sem_philo_full);
	sem_unlink(t->sem_philo_dead);
	sem_unlink(t->sem_stop);
}

void 	cleanup_table(t_table *t, int exit_code)
{
	if (!t)
		return ;
	pthread_join(t->gluttony_monitor, NULL);
	pthread_join(t->famine_monitor, NULL);
	sem_close(t->sem_forks);
	sem_clone(t->sem_print);
	sem_close(t->sem_philo_full);
	sem_close(t->sem_philo_dead);
	sem_close(t->sem_stop);
	unlink_sems(t);
	free_table(t);
}

