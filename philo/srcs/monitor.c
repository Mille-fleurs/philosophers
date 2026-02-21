/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:41:35 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:36:29 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_philo(t_table *t, int p_id)
{
	print_status(t, p_id, DIED);
	set_int(&t->end_mutex, &t->end, 1);
}

static int	is_dead(t_table *t, t_philo *p)
{
	long	curr_time;
	long	last_meal_time;

	curr_time = get_current_time();
	last_meal_time = get_long(&p->philo_mutex, &p->last_meal_time);
	if (curr_time - last_meal_time >= t->time_die)
		return (1);
	return (0);
}

static int	is_full(t_table *t, t_philo *p, int *full_count)
{
	int	is_full;

	is_full = get_int(&p->philo_mutex, &p->is_full);
	if (is_full == 1)
		(*full_count)++;
	if (*full_count == t->philo_num)
		return (1);
	return (0);
}

void	*monitor(void *data)
{
	int		i;
	int		full_count;
	t_table	*t;

	t = (t_table *)data;
	while (!get_int(&t->end_mutex, &t->end))
	{
		i = -1;
		full_count = 0;
		while (++i < t->philo_num)
		{
			if (is_full(t, &t->philos[i], &full_count))
			{
				set_int(&t->end_mutex, &t->end, 1);
				return (NULL);
			}
			if (is_dead(t, &t->philos[i]))
			{
				kill_philo(t, i + 1);
				return (NULL);
			}
		}
	}
	return (data);
}
