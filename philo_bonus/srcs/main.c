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

int		simulation_finihsed(t_table *t)
{
	int	ret;

	sem_wait(t->sem_stop);
	ret = t->sim_stop;
	sem_post(t->sem_stop);
}

static int	start_simulation(t_table *t)
{
	int		i;
	pid_t	pid;

	t->start_time = get_current_time() + (t->philo_num * 2 * 10);
	i = 0;
	while (i < t->philo_num)
	{
		pid = fork();
		if (pid < 0)
			return (error_failure(STR_ERR_FORK, NULL, t));
		if (pid > 0)
			t->pids[i] = pid;
		if (pid == 0)
		{
			t->current_philo = t->philos[i];
			philo_process(t);
			exit(0);
		}
		return (1);
	}
}

static int	handle_child_exit(t_table *t, pid_t *pids)
{
	int	i;
	int child_exit_code;
	int exit_code;

	i = 0;
	while (i < t->philo_num)
	{
		if (*pids && waitpid(t->pids[i], &child_exit_code, WNOHANG) > 0)
		{
			exit_code = WEXITSTATUS(child_exit_code);
			if (exit_code == CHILD_EXIT_PHILO_DEAD)
				return (kill_philos(t, -1));
			if (exit_code == CHILD_EXIT_PHILO_FULL)
			{
				if 
			}
		}
	}

}

static int	stop_simulation(t_table *t)
{

}

int	main(int ac, char **av)
{
	t_table	*table;
	int ret;

	table = NULL;
	ret = 0;
	if (ac != 5 && ac != 6)
		return (error_msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!is_valid_arg(ac, av))
		return (EXIT_FAILURE);
	table = init_table(ac, av, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	if (!stop_simulation(table))
		return (cleanup_table(table, EXIT_FAILURE));
	return (cleanup_table(table, EXIT_SUCCESS));
}

