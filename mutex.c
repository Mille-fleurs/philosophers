/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:49 by chitoupa          #+#    #+#             */
/*   Updated: 2026/01/28 14:17:22 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_mutex_error(int status, t_op op)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (op == LOCK || op == UNLOCK))
		error_msg("The value specified by mutex is invalid.\n");
	else if (status == EINVAL && (op == INIT || op ==DESTROY))
		error_msg("The value specified by attr is invalid.\n");
	else if (status == ENOMEM)
		error_msg("The process cannot allocate enough memory to create another mutex.\n");
	else if (status == EPERM)
		error_mdg("The current thread does not hold a lock on mutex.\n");
	else if (status == EBUSY)
		error_msg("Mutex is locked.\n");	
	else if (status == EDEADLK)
		error_msg("A deadlock would occur if the thread blocked waiting for mutex.\n");
	return ;
}

void safe_mutex_handle(t_mtx *mutex, t_op code)
{
	if (code == LOCK)
		handle_utex_error(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), code);
	else
		error_msg("Error\n");
}
