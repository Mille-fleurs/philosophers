/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:45:24 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:37:37 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	unlock_forks_end(t_philo *p, int must_set)
{
	int	ret;

	ret = 1;
	if (must_set == 1)
		end_on_error(p->table);
	if (!safe_mutex_handle(&p->second_f->mutex, UNLOCK))
		ret = 0;
	if (!safe_mutex_handle(&p->first_f->mutex, UNLOCK))
		ret = 0;
	return (ret);
}

static int	eat_routine(t_philo *p)
{
	int	meals;

	if (!set_long(&p->philo_mutex, &p->last_meal_time, get_current_time()))
		return (unlock_forks_return(p, 1));
	if (!simulation_finished(p->table))
		print_status(p->table, p->id, EATING);
	precise_sleep(p->table, p->table->time_eat);
	meals = get_int(&p->philo_mutex, &p->meals_eaten);
	if (meals < 0)
		return (unlock_forks_return(p, 1));
	if (!set_int(&p->philo_mutex, &p->meals_eaten, meals + 1))
		return (unlock_forks_return(p, 1));
	if (p->table->meal_num > 0 && meals + 1 >= p->table->meal_num)
	{
		if (!set_int(&p->philo_mutex, &p->is_full, 1))
			return (unlock_forks_return(p, 1));
	}
	if (!unlock_forks_end(p, 1))
		return (0);
	return (1);
}

static int	take_fork(t_philo *p)
{
	if (!safe_mutex_handle(&p->first_f->mutex, LOCK))
		return (end_on_error(p->table), 0);
	if (simulation_finished(p->table))
	{
		safe_mutex_handle(&p->first_f->mutex, UNLOCK);
		return (0);
	}
	if (!simulation_finished(p->table))
		print_status(p->table, p->id, GOT_FORK_1);
	if (!safe_mutex_handle(&p->second_f->mutex, LOCK))
	{
		safe_mutex_handle(&p->first_f->mutex, UNLOCK);
		return (end_on_error(p->table), 0);
	}
	if (simulation_finished(p->table))
		return (unlock_forks_return(p, 0));
	if (!simulation_finished(p->table))
		print_status(p->table, p->id, GOT_FORK_2);
	return (1);
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
		think_routine(p, 0);
		if (simulation_finished(p->table))
			break ;
		if (!take_fork(p))
			break ;
		if (!eat_routine(p))
			break ;
		if (!simulation_finished(p->table))
			print_status(p->table, p->id, SLEEPING);
		precise_sleep(p->table, p->table->time_sleep);
	}
	return (NULL);
}
