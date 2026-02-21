/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:41:50 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:37:04 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	precise_sleep(t_table *t, long ms)
{
	time_t	start;

	start = get_current_time();
	while (!simulation_finished(t))
	{
		if ((get_current_time() - start) >= ms)
			break;
		usleep(200);
	}
}

void start_delay(time_t start_time)
{
	while (get_current_time() < start_time)
		continue;
}