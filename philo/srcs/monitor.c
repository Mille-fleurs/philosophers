/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:41:35 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/27 09:51:54 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_philo(t_table *t, int p_id)
{
	set_int(&t->end_mutex, &t->end, 1);
	print_status(t, p_id, DIED);
}

static int	is_dead(t_table *t, t_philo *p)
{
	long	curr;
	long	last_meal;

	curr = get_current_time();
	last_meal = get_long(&p->philo_mutex, &p->last_meal_time);
	printf("%s%ld ms : remaining ms is : %ld%s\n", PURPLE, curr, t->time_die - (curr - last_meal), NC);
	if (curr - last_meal >= t->time_die)
		return (1);
	return (0);
}

static int	is_full(t_table *t, t_philo *p, int *full_count)
{
	int	is_full;

	if (t->meal_num == -1)
		return (0);
	is_full = get_int(&p->philo_mutex, &p->is_full);
	if (is_full == 1)
		(*full_count)++;
	if (*full_count == t->philo_num)
		return (1);
	printf("%s%ld ms : %d philos out of %d are full%s\n", PURPLE, get_current_time(), *full_count, p->id, NC);
	return (0);
}

void	*monitor(void *data)
{
	int		i;
	int		full_count;
	t_table	*t;

	t = (t_table *)data;
	while (!simulation_finished(t))
	{
		i = -1;
		full_count = 0;
		while (++i < t->philo_num)
		{
			if (is_dead(t, &t->philos[i]))
			{
				kill_philo(t, i + 1);
				return (NULL);
			}
			if (is_full(t, &t->philos[i], &full_count))
			{
				set_int(&t->end_mutex, &t->end, 1);
				return (NULL);
			}
		}
		precise_sleep(t, 1);
	}
	return (NULL);
}
