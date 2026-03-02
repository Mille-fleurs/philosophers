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
        sem_post(p->sem_meal);
        print_status(p, DIED);
        sem_post(p->table->sem_philo_dead);
        exit(CHILD_EXIT_PHILO_DEAD);
    }
    if (p->table->meal_num != -1 && p->is_full)
    {
        sem_post(p->sem_meal);
        sem_post(p->table->sem_philo_full);
        exit(CHILD_EXIT_PHILO_FULL);
    }
    sem_post(p->sem_meal);
    return (0);
}

void	*personal_monitor(void *data)
{
    t_philo *p;

    p = (t_philo *)data;
    while (1)
    {
        check_end_condition(p);
        precise_sleep(1);
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
    sem_post(t->sem_stop);
    return (NULL);
}

void    *death_monitor(void *data)
{
    t_table *t;

    t = (t_table *)data;
    sem_wait(t->sem_philo_dead);
    sem_post(t->sem_stop);
    return (NULL);
}

