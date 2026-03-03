/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 13:22:33 by chitoupa          #+#    #+#             */
/*   Updated: 2026/03/03 14:14:04 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	debug_parent(t_table *t, const char *msg, int pid)
{
	long	time;

	if (!DEBUG || !t)
		return ;
	sem_wait(t->sem_print);
	time = get_current_time() - t->start_time;
	if (time < 0)
		time = 0;
	printf("%s[DBG PARENT] %ld ms | %s | pid=%d%s\n", CYAN, time, msg, pid, NC);
	sem_post(t->sem_print);
}

void	debug_monitor(t_table *t, const char *msg, int pid)
{
	long	time;

	if (!DEBUG || !t)
		return ;
	sem_wait(t->sem_print);
	time = get_current_time() - t->start_time;
	if (time < 0)
		time = 0;
	printf("%s[DBG MONITOR] %ld ms | %s | pid=%d%s\n", GREEN, time, msg, pid,
		NC);
	sem_post(t->sem_print);
}

void	debug_philo(t_philo *p, const char *msg)
{
	long	time;

	if (!DEBUG || !p || !p->table)
		return ;
	sem_wait(p->sem_print);
	time = get_current_time() - p->table->start_time;
	if (time < 0)
		time = 0;
	printf("%s[DBG PHILO %d] %ld ms | %s%s\n", PURPLE, p->id, time, msg, NC);
	sem_post(p->sem_print);
}

void	debug_exit_philo(t_philo *p)
{
	long	time;

	if (!DEBUG || !p || !p->table)
		return ;
	sem_wait(p->sem_print);
	time = get_current_time() - p->table->start_time;
	if (time < 0)
		time = 0;
	printf("%s[DBG EXIT PHILO %d] %ld ms | exit_code=%d%s\n", RED, p->id, time,
		p->exit_code, NC);
	sem_post(p->sem_print);
}

void	debug_exit_parent(t_table *t, int pid, int status)
{
	long	time;

	if (!DEBUG || !t)
		return ;
	sem_wait(t->sem_print);
	time = get_current_time() - t->start_time;
	if (time < 0)
		time = 0;
	if (WIFEXITED(status))
		printf("%s[DBG EXIT CHILD] %ld ms | pid=%d exit=%d%s\n", RED, time, pid,
			WEXITSTATUS(status), NC);
	else if (WIFSIGNALED(status))
		printf("%s[DBG EXIT CHILD] %ld ms | pid=%d signal=%d%s\n", RED, time,
			pid, WTERMSIG(status), NC);
	sem_post(t->sem_print);
}
