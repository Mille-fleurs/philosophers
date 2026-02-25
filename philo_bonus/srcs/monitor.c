/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:47:44 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/24 20:40:04 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int     check_end_condition(t_table *t, t_philo *p)
{
    sem_wait(p->sem_meal);
    if (get_current_time() - p->last_meal_time >= t->time_to_die)
    {
        print_status(p, DIED);
        sem_post(p->sem_philo_dead);
        return (1);
    }
    if (t->meal_num != 1)
    {
        if (p->meals_eaten >= t->meal_num)
        {
            sem_post(p->sem_philo_full);
            return (1);
        }
    }
    sem_post(p->sem_meal);
    return (0);
}

void	*personal_monitor(void *data)
{
    t_philo *p;
    t_table *t;

    p = (t_philo *)data;
    t = p->table;

    if (t->meal_num == -1)
        return (NULL);
    while (1)
    {
        if (check_end_condition(t, p))
            break;
        precise_sleep(1);
    }
    return (NULL);
}

void    *meal_monitor(void *data)
{
    t_table *t;
    unsigned int i;

    t = (t_table *)data;
    if (t->meal_num == -1)
        return (NULL);
    i = 0;
    while (i < t->philo_num)
    {  
        sem_wait(t->sem_philo_full);
        i++;
    }
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
