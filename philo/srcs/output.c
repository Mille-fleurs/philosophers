/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:54:18 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/17 18:15:23 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_table *t, int p_index, t_status code)
{
    long long time;

	if (!safe_mutex_handle(&t->print_mutex, LOCK))
		return (end_on_error(t));
	if (!simulation_finished(t) || code == DIED)
	{
    	time = (long long)(get_current_time() - t->start_time);
		if (code == EATING)
			printf("%lld %d is eating\n", time, p_index);
		else if (code == SLEEPING)
			printf("%lld %d is sleeping\n", time, p_index);
		else if (code == THINKING)
			printf("%lld %d is thinking\n", time, p_index);
		else if (code == GOT_FORK_1 || code == GOT_FORK_2)
			printf("%lld %d has taken a fork\n", time, p_index);
		else if (code == DIED)
			printf("%lld %d died\n", time, p_index);
	}
	if (!safe_mutex_handle(&t->print_mutex, UNLOCK))
		return (end_on_error(t));
}

