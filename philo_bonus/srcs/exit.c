/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:47:10 by chitoupa          #+#    #+#             */
/*   Updated: 2026/03/03 14:14:12 by chitoupa         ###   ########.fr       */
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

int	error_exit(char *s, t_table *t, int sem_opened, int children_created)
{
	cleanup_table(t, sem_opened, children_created);
	return (error_msg(s, NULL, 0));
}

t_table	*init_error(char *s, t_table *t, int sem_opened, int children_created)
{
	cleanup_table(t, sem_opened, children_created);
	error_msg(s, NULL, 0);
	return (NULL);
}

// int sem_failure(t_table *t, int ret)
// {
// 	sem_error_cleanup(t);
// 	printf(STR_ERR_SEM, STR_PROG_NAME);
// 	return (ret);
// }

// void	*init_failure_exit(t_table *t)
// {
// 	if (t->pids)
// 	{
// 		free(t->pids);
// 		t->pids = NULL;
// 	}
// 	sem_error_cleanup(t);
// 	free(t);
// 	return (NULL);
// }
