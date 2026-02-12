/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:52 by chitoupa          #+#    #+#             */
/*   Updated: 2026/01/28 14:17:25 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// pthread_create()
// EAGAIN: “Insufficient resources to create another thread” (or system/user thread limit reached).
// EINVAL: “Invalid settings in attr” (bad pthread_attr_t, bad stack size, etc.).
// EPERM: “No permission to set the scheduling policy/parameters specified in attr.”
// pthread_join()
// EINVAL: “The thread is not joinable” (e.g., it was detached) or “another thread is already joining it”.
// ESRCH: “No thread with the given ID could be found.”
// EDEADLK: “Deadlock detected” (e.g., trying to join yourself, or circular join situation).
// pthread_detach()
// EINVAL: “The thread is not a joinable thread” (already detached, or invalid state).
// ESRCH: “No thread with the given ID could be found.”

void	handle_thread_error(int status, t_op op)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_msg("Insufficient resources to create another thread\n");
	else if (status == EINVAL && (op == JOIN || op == DETATCH))
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

void safe_thread_handle(t_mtx *mutex, t_op code)
{
	if (code == LOCK)
		handle_utex_error(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), code);
	else
		error_msg("Error\n");
}
