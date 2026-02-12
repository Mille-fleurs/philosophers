/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:52 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/12 21:11:20 by chitoupa         ###   ########.fr       */
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
		error_msg("The thread is not a joinable thread\n");
	else if (status == EINVAL && op == CREATE)
		error_msg("Invalid settings in attr\n");
	else if (status == EPERM)
		error_mdg("No permission to set the scheduling policy/parameters specified in attr.\n");
	else if (status == ESRCH)
		error_msg("No thread with the given ID could be found.\n");	
	else if (status == EDEADLK)
		error_msg("Deadlock detected.\n");
	return ;
}

void safe_thread_handle(t_mtx *mutex, t_op code)
{
	if (code == CREATE)
		handle_utex_error(pthread_mutex_create(mutex), code);
	else if (code == UNLOCK)
		handle_mutex_error(pthread_mutex_join(mutex), code);
	else if (code == INIT)
		handle_mutex_error(pthread_mutex_detatch(mutex, NULL), code);
	else
		error_msg("Error\n");
}
