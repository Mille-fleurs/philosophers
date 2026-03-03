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
	}
	if (pthread_create(&t->death_monitor, NULL, death_monitor, t) != 0)
		return (0);
	return (1);
}

static void handle_pid(t_table *t, pid_t pid, int pos)
{
	t_philo *p;

	if (pid < 0)
	{
		kill_and_wait_children(t);
		error_exit(STR_ERR_FORK, t, 1, 1);
		return ;
	}
	if (pid == 0)
	{
		p = t->philos[pos];
		philosopher(p);
		exit(EXIT_SUCCESS);
	}
	t->pids[pos] = pid;
	debug_parent(t, "fork created", pid);
}

static int	start_simulation(t_table *t)
{
	int	i;
	pid_t			pid;

	t->start_time = get_current_time();
	i = -1;
	while (++i < t->philo_num)
	{
		pid = fork();
		handle_pid(t, pid, i);
	}
	if (!create_parent_threads(t))
		return (error_exit(STR_ERR_PTHREAD, t, 1, 1));
	debug_monitor(t, "parents monitor started", -1);
	return (1);
}

static void	stop_simulation(t_table *t)
{
	int i;
    int status;

	sem_wait(t->sem_stop);
	unblock_monitor_threads(t);
    if (!t || !t->pids)
        return ;
    i = -1;
    while (++i < t->philo_num)
    {   
        if (t->pids[i] > 0)
            kill(t->pids[i], SIGTERM);
    }
    i = -1;
    while (++i < t->philo_num)
    {
        if (t->pids[i] > 0)
		{
            waitpid(t->pids[i], &status, 0);
			debug_parent(t, "child reaped", t->pids[i]);
			debug_exit_parent(t, t->pids[i], status);
		}
    }
	join_monitor_threads(t);
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
