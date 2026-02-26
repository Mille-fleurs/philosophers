/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:45:15 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/26 22:04:12 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_on_error(t_table *t)
{
	set_int(&t->end_mutex, &t->end, 1);
}

void	only_one_philo(t_table *t)
{
	print_status(t, t->philos[0].id, GOT_FORK_1);
	precise_sleep(t, t->time_die);
	print_status(t, 1, DIED);
	set_int(&t->end_mutex, &t->end, 1);
}

static void	wait_until_ready(t_table *t)
{
	int	ready;

	ready = -1;
	while (1)
	{
		ready = get_int(&t->table_mutex, &t->threads_ready);
		if (ready == 1)
			break ;
		precise_sleep(t, 1);
	}
}

int	preparation(t_table *t)
{
	wait_until_ready(t);
	while (!simulation_finished(t) && get_current_time() < t->start_time)
		precise_sleep(t, 1);
	printf("%s%ld ms : All Philosopher ready%s\n", RED, get_current_time(), NC);
	return (1);
}
