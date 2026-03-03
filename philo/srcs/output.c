/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 13:18:59 by chitoupa          #+#    #+#             */
/*   Updated: 2026/03/03 14:04:10 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_table *t, int p_index, t_status code)
{
	long long	time;

	safe_mutex_handle(&t->print_mutex, LOCK);
	if (!simulation_finished(t) || code == DIED)
	{
		time = (long long)(get_current_time() - t->start_time);
		if (time < 0)
			time = 0;
		if (code == EATING)
			printf("%lld %d is eating\n", time, p_index);
		else if (code == SLEEPING)
			printf("%lld %d is sleeping\n", time, p_index);
		else if (code == THINKING)
			printf("%lld %d is thinking\n", time, p_index);
		else if (code == GOT_FORK_1 || code == GOT_FORK_2)
			printf("%lld %d has taken a fork\n", time, p_index);
		else if (code == DIED)
		{
			printf("%lld %d died\n", time, p_index);
			safe_mutex_handle(&t->print_mutex, UNLOCK);
			return ;
		}
	}
	safe_mutex_handle(&t->print_mutex, UNLOCK);
}

void	write_outcome(t_table *table)
{
	int	i;
	int	full_count;

	if (table->meal_num == -1)
		return ;
	full_count = 0;
	i = -1;
	while (++i < table->philo_num)
	{
		if (get_int(&table->philos[i].philo_mutex,
				&table->philos[i].meals_eaten) >= table->meal_num)
			full_count++;
	}
	safe_mutex_handle(&table->print_mutex, LOCK);
	printf("%s%d/%d philosophers had at least %d meals.%s\n", RED, full_count,
		table->philo_num, table->meal_num, NC);
	safe_mutex_handle(&table->print_mutex, UNLOCK);
	return ;
}

void	debug_monitor(t_table *t, char *msg, int id)
{
	if (!DEBUG)
		return ;
	pthread_mutex_lock(&t->print_mutex);
	printf("%s[DBG] %ld %s (%d)%s\n", RED, get_current_time(), msg, id, NC);
}

void	debug_philo(t_philo *p, const char *msg)
{
	if (!DEBUG)
		return ;
	safe_mutex_handle(&p->table->print_mutex, LOCK);
	printf("%s[DBG] %ld ms | philo %d | %s%s\n", PURPLE, get_current_time()
		- p->table->start_time, p->id, msg, NC);
	safe_mutex_handle(&p->table->print_mutex, UNLOCK);
}
