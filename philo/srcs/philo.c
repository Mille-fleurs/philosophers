/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:45:24 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/27 21:08:40 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void debug_philo(t_philo *p, const char *msg)
{
	if (!DEBUG)
		return ;
	safe_mutex_handle(&p->table->print_mutex, LOCK);
	printf("%s[DBG] %ld ms | philo %d | %s%s\n", PURPLE, get_current_time() - p->table->start_time, p->id, msg, NC);
	safe_mutex_handle(&p->table->print_mutex, UNLOCK);
}

static void	eat_routine(t_philo *p)
{
	int	meals;

	set_long(&p->philo_mutex, &p->last_meal_time, get_current_time());
	debug_philo(p, "start_eating");
	if (!simulation_finished(p->table))
		print_status(p->table, p->id, EATING);
	precise_sleep(p->table, p->table->time_eat);
	meals = get_int(&p->philo_mutex, &p->meals_eaten);
	set_int(&p->philo_mutex, &p->meals_eaten, meals + 1);
	debug_philo(p, "finished eating");
	if (p->table->meal_num >= 0 && meals + 1 >= p->table->meal_num)
		set_int(&p->philo_mutex, &p->is_full, 1);
	safe_mutex_handle(&p->second_f->mutex, UNLOCK);
	safe_mutex_handle(&p->first_f->mutex, UNLOCK);
}

static int	take_fork(t_philo *p)
{
	safe_mutex_handle(&p->first_f->mutex, LOCK);
	if (simulation_finished(p->table))
	{
		safe_mutex_handle(&p->first_f->mutex, UNLOCK);
		return (0);
	}
	debug_philo(p, "locked first fork");
	print_status(p->table, p->id, GOT_FORK_1);
	safe_mutex_handle(&p->second_f->mutex, LOCK);
	if (simulation_finished(p->table))
	{
		safe_mutex_handle(&p->second_f->mutex, UNLOCK);
		safe_mutex_handle(&p->first_f->mutex, UNLOCK);
		return (0);
	}
	debug_philo(p, "locked second fork");
	print_status(p->table, p->id, GOT_FORK_2);
	return (1);
}

static void	think_routine(t_philo *p, int silent)
{
	long	time_to_think;
	long	last_meal_time;

	last_meal_time = get_long(&p->philo_mutex, &p->last_meal_time);
	time_to_think = (p->table->time_die - (get_current_time() - last_meal_time)
			- p->table->time_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (!simulation_finished(p->table) && silent == 0)
		print_status(p->table, p->id, THINKING);
	debug_philo(p, "start_thinking");
	precise_sleep(p->table, time_to_think);
}

void	*philosopher(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	wait_until_ready(p->table);
	if (p->table->philo_num == 1)
		return (only_one_philo(p->table), NULL);
	debug_philo(p, "loop start");
	while (!simulation_finished(p->table))
	{
		if (!take_fork(p))
			continue ;
		if (simulation_finished(p->table))
		{
			safe_mutex_handle(&p->second_f->mutex, UNLOCK);
			safe_mutex_handle(&p->first_f->mutex, UNLOCK);
			break ;
		}
		eat_routine(p);
		if (!simulation_finished(p->table))
			print_status(p->table, p->id, SLEEPING);
		precise_sleep(p->table, p->table->time_sleep);
		if (!simulation_finished(p->table))
			think_routine(p, 0);
	}
	return (NULL);
}
