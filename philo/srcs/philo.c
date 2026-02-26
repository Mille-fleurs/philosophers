/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:45:24 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/26 20:09:04 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_routine(t_philo *p)
{
	int	meals;

	set_long(&p->philo_mutex, &p->last_meal_time, get_current_time());
	if (!simulation_finished(p->table))
		print_status(p->table, p->id, EATING);
	precise_sleep(p->table, p->table->time_eat);
	meals = get_int(&p->philo_mutex, &p->meals_eaten);
	set_int(&p->philo_mutex, &p->meals_eaten, meals + 1);
	if (p->table->meal_num >= 0 && meals + 1 >= p->table->meal_num)
		set_int(&p->philo_mutex, &p->is_full, 1);
	safe_mutex_handle(&p->second_f->mutex, UNLOCK);
	safe_mutex_handle(&p->first_f->mutex, UNLOCK);
}

static void	take_fork(t_philo *p)
{
	safe_mutex_handle(&p->first_f->mutex, LOCK);
	if (simulation_finished(p->table))
		safe_mutex_handle(&p->first_f->mutex, UNLOCK);
	if (!simulation_finished(p->table))
		print_status(p->table, p->id, GOT_FORK_1);
	safe_mutex_handle(&p->second_f->mutex, LOCK);
	if (simulation_finished(p->table))
	{
		safe_mutex_handle(&p->second_f->mutex, UNLOCK);
		safe_mutex_handle(&p->first_f->mutex, UNLOCK);
		return ;
	}
	if (!simulation_finished(p->table))
		print_status(p->table, p->id, GOT_FORK_2);
}

static void	think_routine(t_philo *p, int silent)
{
	long	time_to_think;
	long	last_meal_time;

	last_meal_time = get_long(&p->philo_mutex, &p->last_meal_time);
	if (last_meal_time == -1)
	{
		set_int(&p->table->end_mutex, &p->table->end, 1);
		return ;
	}
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
	precise_sleep(p->table, time_to_think);
}

void	*philosopher(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	if (!preparation(p->table))
		return (NULL);
	if (p->table->philo_num == 1)
	{
		only_one_philo(p->table);
		return (NULL);
	}
	while (!simulation_finished(p->table))
	{
		take_fork(p);
		printf("%s%ld ms : philo[%d] taken two forks%s\n", CYAN, get_current_time(), p->id, NC);
		eat_routine(p);
		printf("%s%ld ms : philo[%d] finish to eat%s\n", CYAN, get_current_time(), p->id, NC);
		if (!simulation_finished(p->table))
			print_status(p->table, p->id, SLEEPING);
		precise_sleep(p->table, p->table->time_sleep);
		think_routine(p, 0);
	}
	return (NULL);
}
