/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:49 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/17 22:05:54 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_mutex_error(int status, t_op op)
{
	if (status == 0)
		return ;
	if (status == EINVAL)
		printf("Invallide mutex.\n");
	else if (status == ENOMEM)
		printf("Not enough memory for mutex.\n");
	else if (status == EPERM && op == UNLOCK)
		printf("Thread tried to unlock a mutex it does not own.\n");
	else if (status == EBUSY)
		printf("Mutex busy (still locked/in use).\n");	
	else if (status == EDEADLK)
		printf("Deadlock detected.\n");
	else
		printf("Mutex error.\n");
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

void	handle_thread_error(int status, t_op op)
{
	if (status == 0)
		return ;
	if (status == EAGAIN && op == CREATE)
		printf("Not enough resources to create thread.\n");
	else if (status == EINVAL && op == CREATE)
		printf("Invalid thread attributes.\n");
	else if (status == EINVAL && (op == JOIN || op == DETACH))
		printf("Invalid thread (not joinable or invalid ID).\n");
	else if (status == ESRCH)
		printf("NO thread with given ID exists.\n");
	else if (status == EDEADLK && op == JOIN)
		printf("Deadlock detected while joining thread.\n");
	else
		printf("Thread operation error.\n");
}

int	safe_thread_handle(pthread_t *t, void *(*routine)(void *), void *arg,
		t_op op)
{
	int	status;

	if (op == CREATE)
		status = pthread_create(t, NULL, routine, arg);
	else if (op == JOIN)
		status = pthread_join(*t, NULL);
	else if (op == DETACH)
		status = pthread_detach(*t);
	else
		return (1);
	if (status != 0)
	{
		handle_thread_error(status, op);
		return (0);
	}
	return (1);
}


