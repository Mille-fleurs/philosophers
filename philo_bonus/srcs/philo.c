/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:48:23 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/27 13:02:04 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void    *only_one_philo(t_philo *p)
{
    sem_wait(p->sem_forks);
    print_status(p, GOT_FORK_1);
    precise_sleep(p->table->time_to_die);
    print_status(p, DIED);
    sem_post(p->table->sem_philo_dead);
    sem_post(p->sem_forks);
    exit(CHILD_EXIT_PHILO_DEAD);
}

static void eat_sleep_routine(t_philo *p)
{
    int become_full;

    become_full = 0;
    if (!take_forks(p))
        return ;
    debug_philo(p, "forks acquired");
    sem_wait(p->sem_meal);
    p->last_meal_time = get_current_time();
    debug_philo(p, "updated last_meal_time");
    p->meals_eaten++;
    if (p->table->meal_num != -1 && p->is_full == 0 && p->meals_eaten >= p->table->meal_num)
    {
        p->is_full = 1;
        become_full = 1;
    }
    sem_post(p->sem_meal);
    print_status(p, EATING);
    precise_sleep(p->table->time_to_eat);
    drop_forks(p);
    debug_philo(p, "forks unlocked");
    if (become_full)
        sem_post(p->table->sem_philo_full);
    print_status(p, SLEEPING);
    precise_sleep(p->table->time_to_sleep);
}

static void	think_routine(t_philo *p, int silent)
{
	long    time_to_think;
    long    lm_time;

    sem_wait(p->sem_meal);
    lm_time = p->last_meal_time;
    sem_post(p->sem_meal);
	time_to_think = (p->table->time_to_die - (get_current_time() - lm_time)
			- p->table->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	print_status(p, THINKING);
	precise_sleep(time_to_think);
}

void    *philosopher(void *data)
{
    t_philo *p;

    p = (t_philo *)data;
    p->last_meal_time = p->table->start_time;
    while (get_current_time() < p->table->start_time)
        usleep(100);
    debug_philo(p, "child started");
    if (p->table->philo_num == 1)
        return (only_one_philo(p), NULL);
    start_monitor(p);
    if (p->id % 2 ==0)
        precise_sleep(1);
    while (!get_stop(p))
    {
        eat_sleep_routine(p);
        if (get_stop(p))
            break ;
        think_routine(p, 0);
        if (get_stop(p))
            break ;
    }
    drop_forks(p);
    debug_philo(p, "forks unlocked");
    debug_exit_philo(p);
    exit(p->exit_code);
}

