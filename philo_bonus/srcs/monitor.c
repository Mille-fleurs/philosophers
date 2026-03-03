/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:47:44 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/27 09:00:37 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int     check_end_condition(t_philo *p)
{
    long    now;

    sem_wait(p->sem_meal);
    now = get_current_time();
    if (now - p->last_meal_time >= p->table->time_to_die)
    {
        p->exit_code = CHILD_EXIT_PHILO_DEAD;
        sem_post(p->sem_meal);
        sem_post(p->table->sem_philo_dead);
        set_stop(p, CHILD_EXIT_PHILO_DEAD);
        sem_wait(p->table->sem_death_lock);
        print_status(p, DIED);
        debug_monitor(p->table, "death detected", p->id);
        return (1);
    }
    sem_post(p->sem_meal);
    return (0);
}

void	*personal_monitor(void *data)
{
    t_philo *p;

    p = (t_philo *)data;
    debug_philo(p, "personal monitor started");
    while (!get_stop(p))
    {
        if (check_end_condition(p))
            return (NULL);
        usleep(500);
    }
    return (NULL);
}

void    *meal_monitor(void *data)
{
    t_table *t;
    int i;

    t = (t_table *)data;
    if (t->meal_num == -1)
        return (NULL);
    i = -1;
    while (++i < t->philo_num)
        sem_wait(t->sem_philo_full);
    debug_monitor(t, "parent received all philos full signal", -1);
    sem_post(t->sem_stop);
    return (NULL);
}

void    *death_monitor(void *data)
{
    t_table *t;

    t = (t_table *)data;
    sem_wait(t->sem_philo_dead);
    debug_monitor(t, "parent received death signal", -1);
    sem_post(t->sem_stop);
    return (NULL);
}

