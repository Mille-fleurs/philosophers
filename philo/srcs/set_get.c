/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:23:57 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:37:40 by chitoupa         ###   ########.fr       */
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

int	get_int(pthread_mutex_t *mtx, int *src)
{
	int	ret;

	if (!safe_mutex_handle(mtx, LOCK))
		return (-1);
	ret = *src;
	if (!safe_mutex_handle(mtx, UNLOCK))
		return (-1);
	return (ret);
}

int	set_long(pthread_mutex_t *mtx, long *dest, long value)
{
	if (!safe_mutex_handle(mtx, LOCK))
		return (0);
	*dest = value;
	if (!safe_mutex_handle(mtx, UNLOCK))
		return (0);
	return (1);
}

long	get_long(pthread_mutex_t *mtx, long *src)
{
	long	ret;

	if (!safe_mutex_handle(mtx, LOCK))
		return (-1);
	ret = *src;
	if (!safe_mutex_handle(mtx, UNLOCK))
		return (-1);
	return (ret);
}

int	simulation_finished(t_table *t)
{
	int	ret;

	ret = get_int(&t->end_mutex, &t->end);
	if (ret < 0)
	{
		set_int(&t->end_mutex, &t->end, 1);
		return (1);
	}
	return (ret);
}
