/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:23:57 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/26 17:05:39 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_int(pthread_mutex_t *mtx, int *dest, int value)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = value;
	safe_mutex_handle(mtx, UNLOCK);
}

int	get_int(pthread_mutex_t *mtx, int *src)
{
	int	ret;

	safe_mutex_handle(mtx, LOCK);
	ret = *src;
	safe_mutex_handle(mtx, UNLOCK);
	return (ret);
}

void	set_long(pthread_mutex_t *mtx, long *dest, long value)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = value;
	safe_mutex_handle(mtx, UNLOCK);
}

long	get_long(pthread_mutex_t *mtx, long *src)
{
	long	ret;

	safe_mutex_handle(mtx, LOCK);
	ret = *src;
	safe_mutex_handle(mtx, UNLOCK);
	return (ret);
}

int	simulation_finished(t_table *t)
{
	int	ret;

	ret = get_int(&t->end_mutex, &t->end);
	return (ret);
}
