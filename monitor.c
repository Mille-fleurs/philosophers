/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:41:35 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/15 21:06:58 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// detecting if a philosopher dies 
// detecting if all philosophers have eaten enough (if meal_num is set)
// stopping the simulation safely

void    kill_philo(t_table *t, int p_id)
{
    print_status(t->start_time, p_id, DIED);
    set_int(&t->end_mutex, &t->end, 1);
}

int     monitor(t_table *t)
{
    int i;
    int is_full;
    int full_count;
    long curr_time;
    long last_meal_time;

    while (!get_int(&t->end_mutex, &t->end))
    {
        i = -1;
        full_count = 0;
        while (++i < t->philo_num)
        {
            is_full = get_int(&t->philos[i].philo_mutex, &t->philos[i].is_full);
            if (is_full == 1)
                full_count++;
            curr_time = get_current_time();
            last_meal_time = get_long(&t->philos[i].philo_mutex, &t->philos[i].last_meal_time);
            if (curr_time - last_meal_time >= t->t_die)
                return (kill_philo(t, i + 1), 0);
            if (full_count == t->philo_num)
                return (set_int(&t->end_mutex, &t->end, 1), 0);
        }
    }
    return (1);
}
