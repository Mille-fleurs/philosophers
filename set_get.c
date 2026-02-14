/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:23:57 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/14 22:01:32 by chitoupa         ###   ########.fr       */
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

int	set_long_long(pthread_mutex_t *mtx, long long *dest, long long value)
{
	if (!safe_mutex_handle(mtx, LOCK))
		return (0);
	*dest = value;
	if (!safe_mutex_handle(mtx, UNLOCK))
		return (0);
	return (1);
}
