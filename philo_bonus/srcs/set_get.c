/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:17:47 by chitoupa          #+#    #+#             */
/*   Updated: 2026/03/03 14:15:09 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_int(sem_t *lock, int *dest, int value)
{
	sem_wait(lock);
	*dest = value;
	sem_post(lock);
}

int	get_int(sem_t *lock, int *src)
{
	int	ret;

	sem_wait(lock);
	ret = *src;
	sem_post(lock);
	return (ret);
}

long	set_long(sem_t *lock, long *dest, long value)
{
	sem_wait(lock);
	*dest = value;
	sem_post(lock);
}

long	get_long(sem_t *lock, long *src)
{
	long	ret;

	sem_wait(lock);
	ret = *src;
	sem_post(lock);
	return (ret);
}
