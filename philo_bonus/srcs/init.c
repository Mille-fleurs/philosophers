/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:47:22 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:37:01 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int open_global_sems(t_table *t)
{
	t->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0644, t->philo_num);
	if (t->sem_forks == SEM_FAILED)
		return (sem_failure(t, 0));
	t->sem_print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (t->sem_print == SEM_FAILED)
		return (sem_failure(t, 0));
	t->sem_philo_full = sem_open(SEM_FULL, O_CREAT, 0644, t->philo_num);
	if (t->sem_philo_full == SEM_FAILED)
		return (sem_failure(t, 0));
	t->sem_philo_dead = sem_open(SEM_DEAD, O_CREAT, 0644, t->philo_num);
	if (t->sem_philo_dead == SEM_FAILED)
		return (sem_failure(t, 0));
	t->sem_stop = sem_open(SEM_STOP, O_CREAT, 0644, 1);
	if (t->sem_stop == SEM_FAILED)
		return (sem_failure(t, 0));
	return (1);
}

static char	*make_sem_meal_name(char *str, unsigned int id)
{
	char *sem_name;
	char *dup_id;

	dup_id = ft_utoa(id);
	if (!dup_id)
		return (NULL);
	sem_name = malloc(ft_strlen(str) + ft_strlen(dup_id) + 1);
	if (!sem_name)
		return (NULL);
	sem_name[0] = '\0';
	sem_name = ft_strcat(sem_name, str);
	sem_name = ft_strcat(sem_name, dup_id);
	free(dup_id);
	return (sem_name);
}

static int init_one_philo(t_table *t, t_philo **p, int pos)
{
	*p = malloc(sizeof(t_philo));
	if (!*p)
		return (0);
	(*p)->table = t;
	(*p)->id = pos + 1;
	(*p)->meals_eaten = 0;
	(*p)->is_full = 0;
	(*p)->last_meal_time = 0;
	(*p)->personal_death = (pthread_t)0;
	(*p)->sem_forks = t->sem_forks;
	(*p)->sem_print = t->sem_print;
	(*p)->sem_philo_full = t->sem_philo_full;
	(*p)->sem_philo_dead = t->sem_philo_dead;
	(*p)->sem_meal_name = set_local_sem_name(SEM_MEAL, (*p)->id);
	if (!(*p)->sem_meal_name)
		return (0);
	(*p)->sem_meal = NULL;
	return (1);
}

static int	init_philos(t_table *t)
{
	int	i;
	
	t->philos = NULL;
	t->current_philo = NULL;
	t->philos = malloc(sizeof (t_philo *) * t->philo_num);
	if (!t->philos)
		return (error_failure(STR_ERR_MALLOC, NULL, t));
	i = 0;
	while (i < t->philo_num)
	{
		t->philos[i] = NULL;
		if (!init_one_philo(t, &t->philos[i], i))
			return (error_failure(STR_ERR_MALLOC, NULL, t));
		i++;
	}
	return (1);
}

t_table *init_table(int ac, char **av)
{
	t_table *t;
	
	t = malloc(sizeof(t_table));
	if (!t)
		return (NULL);
	memset(t, 0, sizeof(*t));
	t->philos = NULL;
	t->pids = NULL;
	if (!parse_arg(t, ac, av))
		return (free(t), NULL);
	unlink_global_sems();
	if (!open_global_sems(t))
		return (free(t), NULL);
	t->pids = malloc(sizeof(pid_t) * t->philo_num);
	if (!t->pids)
		return (init_failure_exit(NULL, t));
	memset(t->pids, 0, sizeof(pid_t) * t->philo_num);
	if (!init_philos(t))
		return (init_failure_exit(t->pids, t));
	return (t);
}

