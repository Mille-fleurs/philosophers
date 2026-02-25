/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:47:35 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:37:24 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	create_parents_thread(t_table *t)
{
	if (t->meal_num == -1)
	{
		if (pthread_create(&t->meal_monitor, NULL, meal_monitor, t) != 0)
			return (0);
	}
	if (pthread_create(&t->death_monitor, NULL, death_monitor, t) != 0)
		return (0);
	return (1);
}

static int	start_simulation(t_table *t)
{
	unsigned int		i;
	pid_t	pid;
	t_philo	*p;

	t->start_time = get_current_time() + (t->philo_num * 2 * 10);
	i = -1;
	while (++i < t->philo_num)
	{
		pid = fork();
		if (pid < 0)
			return (error_failure(STR_ERR_FORK, NULL, t, i));
		if (pid > 0) //parent
			t->pids[i] = pid;
		if (pid == 0) //child
		{
			p = t->philos[i];
			philosopher(p);
			exit(EXIT_SUCCESS);
		}
	}
	if (!create_parents_thread(t))
		return (error_failure(STR_ERR_PTHREAD, NULL, t, i));
	return (1);
}

static int	handle_child_exit(pid_t *pid)
{
	int status;
	int exit_code;
	pid_t ret;

	if (!pid || *pid == 0)
		return (0);

	ret = waitpid(*pid, &status, WNOHANG);
	if (ret <= 0)
		return (0);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code == CHILD_EXIT_PHILO_DEAD)
			return (-1);
		if (exit_code == CHILD_EXIt_ERR_PTHREAD
			|| exit_code == CHILD_EXIT_ERR_SEM)
			return (-1);
		if (exit_code == CHILD_EXIT_PHILO_FULL)
			return (1);
	}
	*pid = 0;
	if (WIFSIGNALED(status))
		return (-1);
	return (0);
}

static int	stop_simulation(t_table *t)
{
	unsigned int	i;
	int res;
	unsigned int full_count;
	
	full_count = 0;
	res = 0;
	while (1)
	{
		i = 0;
		while (i < t->philo_num)
		{
			res = handle_child_exit(&t->pids[i]);
			if (res == -1)
				return (kill_philos(t, -1));
			if (res == 1 && t->meal_num != -1)
			{
				full_count++;
				if (full_count == t->philo_num)
					return (kill_philos(t, 1));
			}
			i++;
		}
		precise_sleep(1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac != 5 && ac != 6)
		return (error_msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!is_valid_arg(ac, av))
		return (EXIT_FAILURE);
	table = init_table(ac, av);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	if (stop_simulation(table) == -1)
		return (cleanup_table(table, EXIT_FAILURE));
	return (cleanup_table(table, EXIT_SUCCESS));
}

