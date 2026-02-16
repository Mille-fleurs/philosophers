/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:56:20 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/15 21:06:48 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    start_simulation(t_table *t)
{
    int     i;

    t->start_time = get_current_time() + (t->philo_num * 2 * 10);
    i = -1;
    while (++i < t->philo_num)
    {
        if (!set_long(&t->philos[i].philo_mutex, &t->philos[i].last_meal_time, t->start_time))
            return (0);
    }
    i = -1;
    while (++i < t->philo_num)
    {
        if (!safe_thread_handle(&t->philos[i].thread_id, philosopher, &t->philos[i], CREATE))
            return (cleanup_table(t, t->philo_num), 0);
    }
    if (t->philo_num > 1)
    {
        if (!safe_thread_handle(&t->monitor, monitor, t, CREATE))
            return (cleanup_table(t, t->philo_num), 0);
    }
    i = -1;
	set_int(&t->table_mutex, &t->threads_ready, 1);
    return (1);
}

int     stop_simulation(t_table *t, int forks_inited)
{
    int     i;

    if (!t)
        return (0);
    i = -1;
    while (++i < t->philo_num)
    {
        if (!safe_thread_handle(&t->philos[i].thread_id, NULL, NULL, JOIN))
            return (cleanup_table(t, forks_inited), 0);
    }
    if (t->philo_num > 1)
    {
        if (!safe_thread_handle(&t->monitor, NULL, NULL, JOIN))
            return (cleanup_table(t, forks_inited), 0);
    }
    cleanup_table(t, t->philo_num);
    return (1);
}