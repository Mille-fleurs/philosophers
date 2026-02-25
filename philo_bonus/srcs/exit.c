/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:47:10 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:37:54 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	error_msg(char *str, char *detail, int ret)
{
	if (!detail)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, detail);
	return (ret);
}

int	error_failure(char *s, char *details, t_table *t, int child_id)
{
	if (t && child_id > 0)
		kill_philos(t, EXIT_FAILURE);
	if (t)
		free_table(t);
	return (error_msg(s, details, 0));
}

int sem_failure(t_table *t, int ret)
{
	sem_error_cleanup(t);
	printf(STR_ERR_SEM, STR_PROG_NAME);
	return (ret);
}

void	*init_failure_exit(t_table *t)
{
	if (t->pids)
	{
		free(t->pids);
		t->pids = NULL;
	}
	sem_error_cleanup(t);
	free(t);
	return (NULL);
}

