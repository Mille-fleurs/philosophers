/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:49 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/15 21:07:31 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_mutex_error(int status, t_op op)
{
	if (status == 0)
		return ;
	if (status == EINVAL)
		error_msg("Invallide mutex.\n");
	else if (status == ENOMEM)
		error_msg("Not enough memory for mutex.\n");
	else if (status == EPERM && op == UNLOCK)
		error_msg("Thread tried to unlock a mutex it does not own.\n");
	else if (status == EBUSY)
		error_msg("Mutex busy (still locked/in use).\n");	
	else if (status == EDEADLK)
		error_msg("Deadlock detected.\n");
	else
		error_msg("Mutex error.\n");
	return ;
}

int safe_mutex_handle( pthread_mutex_t *mtx, t_op code)
{
	int status;

	if (code == LOCK)
		status = pthread_mutex_lock(mtx);
	else if (code == UNLOCK)
		status = pthread_mutex_unlock(mtx);
	else if (code == INIT)
		status = pthread_mutex_init(mtx, NULL);
	else if (code == DESTROY)
		status = pthread_mutex_destroy(mtx);
	else
		return (0);
	if (status != 0)
	{
		handle_mutex_error(status, code);
		return (0);
	}
	return (1);
}
