/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:47:10 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:37:54 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	create_parent_threads(t_table *t)
{
	if (t->meal_num != -1)
	{
		if (pthread_create(&t->meal_monitor, NULL, meal_monitor, t) != 0)
			return (0);
		pthread_detach(t->meal_monitor);
	}
	if (pthread_create(&t->death_monitor, NULL, death_monitor, t) != 0)
		return (0);
	pthread_detach(t->death_monitor);
	return (1);
}

static int	start_simulation(t_table *t)
{
	int	i;
	pid_t			pid;
	t_philo			*p;

	t->start_time = get_current_time() + (t->philo_num * 2 * 10);
	i = -1;
	while (++i < t->philo_num)
	{
		pid = fork();
		if (pid < 0)
			return (error_exit(STR_ERR_FORK, t, 1, 1));
		if (pid == 0)
		{
			p = t->philos[i];
			philosopher(p);
			exit(EXIT_SUCCESS);
		}
		t->pids[i] = pid;
	}
	if (!create_parent_threads(t))
		return (error_exit(STR_ERR_PTHREAD, t, 1, 1));
	return (1);
}

static void	stop_simulation(t_table *t)
{
	int	i;
	int	status;

	sem_wait(t->sem_stop);
	kill_philos(t);
	i = 0;
	while (i < t->philo_num)
	{
		if (t->pids[i] > 0)
			waitpid(t->pids[i], &status, 0);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac != 5 && ac != 6)
		return (error_msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!is_valid_arg(ac, av))
		return (EXIT_FAILURE);
	table = init_table(ac, av);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (cleanup_table(table, 1, 1), EXIT_FAILURE);
	stop_simulation(table);
	return (cleanup_table(table, 1, 1), EXIT_SUCCESS);
}