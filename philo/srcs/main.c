/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:46 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:36:26 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		write_outcome(t_table *table);

static int	create_mutex(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_num)
	{
		if (!safe_thread_handle(&t->philos[i].thread_id, philosopher,
				&t->philos[i], CREATE))
			return (0);
		t->threads_created++;
	}
	if (t->philo_num > 1)
	{
		if (!safe_thread_handle(&t->monitor, monitor, t, CREATE))
			return (0);
		t->monitor_created = 1;
	}
	return (1);
}

static int	start_simulation(t_table *t)
{
	int	i;

	t->threads_created = 0;
	t->monitor_created = 0;
	t->start_time = get_current_time() + (t->philo_num * 2 * 10);
	i = -1;
	while (++i < t->philo_num)
	{
		if (!set_long(&t->philos[i].philo_mutex, &t->philos[i].last_meal_time,
				t->start_time))
			return (0);
	}
	if (!create_mutex(t))
	{
		set_int(&t->table_mutex, &t->threads_ready, 1);
		set_int(&t->end_mutex, &t->end, 1);
		return (0);
	}
	if (!set_int(&t->table_mutex, &t->threads_ready, 1))
	{
		set_int(&t->end_mutex, &t->end, 1);
		return (0);
	}
	return (1);
}

static int	stop_simulation(t_table *t)
{
	int	i;

	if (!t)
		return (0);
	i = -1;
	while (++i < t->threads_created)
	{
		if (!safe_thread_handle(&t->philos[i].thread_id, NULL, NULL, JOIN))
			return (0);
	}
	if (t->monitor_created)
	{
		if (!safe_thread_handle(&t->monitor, NULL, NULL, JOIN))
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_table	*table;
	int		ret;

	table = NULL;
	ret = 0;
	if (ac != 5 && ac != 6)
		return (error_msg(STR_USAGE, NULL, 1));
	if (!is_valid_arg(ac, av))
		return (1);
	table = init_table(ac, av);
	if (!table)
		return (1);
	if (!start_simulation(table))
		ret = 1;
	if (!stop_simulation(table))
		ret = 1;
	write_outcome(table);
	cleanup_table(table, table->philo_num, table->philo_num);
	return (ret);
}

void	write_outcome(t_table *table)
{
	int	i;
	int	full_count;

	full_count = 0;
	i = -1;
	while (++i < table->philo_num)
	{
		if (get_int(&table->philos[i].philo_mutex,
				&table->philos[i].meals_eaten) >= table->meal_num)
			full_count++;
	}
	pthread_mutex_lock(&table->print_mutex);
	printf("%d/%d philosophers had at least %d meals.\n", full_count,
		table->philo_num, table->meal_num);
	pthread_mutex_unlock(&table->print_mutex);
	return ;
}
