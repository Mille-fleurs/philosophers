/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:23:57 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/15 21:07:44 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_int(pthread_mutex_t *mtx, int *dest, int value)
{
	if (!safe_mutex_handle(mtx, LOCK))
		return (0);
	*dest = value;
	if (!safe_mutex_handle(mtx, UNLOCK))
		return (0);
	return (1);
}

int get_int(pthread_mutex_t *mtx, int *value)
{
	int ret;

	if (!safe_mutex_handle(mtx, LOCK))
		return (-1);
	ret = *value;
	if (!safe_mutex_handle(mtx, UNLOCK))
		return (-1);
	return (ret);
}

int	set_long_long(pthread_mutex_t *mtx, long long *dest, long long value)
{
	if (!safe_mutex_handle(mtx, LOCK))
		return (0);
	*dest = value;
	if (!safe_mutex_handle(mtx, UNLOCK))
		return (0);
	return (1);
}

int get_long_log(pthread_mutex_t *mtx, long long *value)
{
	long long ret;

	if (!safe_mutex_handle(mtx, LOCK))
		return (0);
	ret = *value;
	if (!safe_mutex_handle(mtx, UNLOCK))
		return (0);
}

int		simulation_finished(t_table *t)
{
	return (get_int(&t->table_mutex, &t->end));
}
