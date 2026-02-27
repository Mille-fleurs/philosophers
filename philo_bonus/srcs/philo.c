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
    return (NULL);
}

static void eat_rountine(t_philo *p)
{
    sem_wait(p->sem_forks);
    print_status(p, GOT_FORK_1);
    sem_wait(p->sem_forks);
    print_status(p, GOT_FORK_2);
    print_status(p, EATING);
    sem_wait(p->sem_meal);
    p->last_meal_time = get_current_time();
    p->meals_eaten++;
    sem_post(p->sem_meal);
    precise_sleep(p->table->time_to_eat);
    sem_post(p->sem_forks);
    sem_post(p->sem_forks);
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
    if (p->table->philo_num == 1)
        return (only_one_philo(p));
    if (pthread_create(&p->personal_monitor, NULL, personal_monitor, p) != 0)
    {
        error_failure(STR_ERR_PTHREAD, NULL, p->table, p->table->philo_num);
        return (NULL);
    }
    if (pthread_detach(p->personal_monitor) != 0)
    {
        error_failure(STR_ERR_PTHREAD, NULL, p->table, p->table->philo_num);
        return (NULL);
    }
    if (p->id % 2 ==0)
        precise_sleep(1);
    while (1)
    {
        eat_sleep_fork(p);
        think_routine(p, 0);
    }
    return (NULL);
}
