/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:52 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/14 22:01:35 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_thread_error(int status, t_op op)
{
	if (status == 0)
		return ;
	if (status == EAGAIN && op == CREATE)
		error_msg("Not enough resources to create thread.\n");
	else if (status == EINVAL && op == CREATE)
		error_msg("Invalid thread attributes.\n");
	else if (status == EINVAL && (op == JOIN || op == DETACH))
		error_msg("Invalid thread (not joinable or invalid ID).\n");
	else if (status == ESRCH)
		error_msg("NO thread with given ID exists.\n");
	else if (status == EDEADLK && op == JOIN)
		error_msg("Deadlock detected while joining thread.\n");
	else
		error_msg("Thread operation error.\n");
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
