/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:47:22 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/24 20:39:48 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int open_global_sems(t_table *t)
{
	t->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0644, t->philo_num);
	if (t->sem_forks == SEM_FAILED)
		return (INIT_ERR_SEM);
	t->sem_print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (t->sem_print == SEM_FAILED)
		return (INIT_ERR_SEM);
	t->sem_philo_full = sem_open(SEM_FULL, O_CREAT, 0644, 0);
	if (t->sem_philo_full == SEM_FAILED)
		return (INIT_ERR_SEM);
	t->sem_philo_dead = sem_open(SEM_DEAD, O_CREAT, 0644, 0);
	if (t->sem_philo_dead == SEM_FAILED)
		return (INIT_ERR_SEM);
	t->sem_stop = sem_open(SEM_STOP, O_CREAT, 0644, 0);
	if (t->sem_stop == SEM_FAILED)
		return (INIT_ERR_SEM);
	t->sem_death_lock = sem_open(SEM_DEATH_LOCK, O_CREAT, 0644, 1);
	if (t->sem_death_lock == SEM_FAILED)
		return (INIT_ERR_SEM);
	return (INIT_OK);
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
		return (free(dup_id), NULL);
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
		return (INIT_ERR_MALLOC);
	memset(*p, 0, sizeof(t_philo));
	(*p)->table = t;
	(*p)->id = pos + 1;
	(*p)->sem_forks = t->sem_forks;
	(*p)->sem_print = t->sem_print;
	(*p)->sem_philo_full = t->sem_philo_full;
	(*p)->sem_philo_dead = t->sem_philo_dead;
	(*p)->sem_death_lock = t->sem_death_lock;
	(*p)->sem_meal_name = make_sem_meal_name(SEM_MEAL, (*p)->id);
	if (!(*p)->sem_meal_name)
		return (free(*p), *p = NULL, INIT_ERR_MALLOC);
	sem_unlink((*p)->sem_meal_name);
	(*p)->sem_meal = sem_open((*p)->sem_meal_name, O_CREAT, 0644, 1);
	if ((*p)->sem_meal == SEM_FAILED)
	{
		free((*p)->sem_meal_name);
		free(*p);
		*p = NULL;
		return (INIT_ERR_SEM);
	}
	return (INIT_OK);
}

static int	init_philos(t_table *t)
{
	int	i;
	int	ret;			
	
	t->philos = malloc(sizeof (t_philo *) * t->philo_num);
	if (!t->philos)
		return (INIT_ERR_MALLOC);
	i = -1;
	while (++i < t->philo_num)
	{
		t->philos[i] = NULL;
		ret = init_one_philo(t, &t->philos[i], i);
		if (ret != INIT_OK)
			return (ret);
	}
	return (INIT_OK);
}

t_table *init_table(int ac, char **av)
{
	t_table *t;
	int		ret;
	
	t = malloc(sizeof(t_table));
	if (!t)
		return (NULL);
	memset(t, 0, sizeof(*t));
	if (!parse_arg(t, ac, av))
		return (cleanup_table(t, 0, 0), NULL);
	unlink_global_sems();
	ret = open_global_sems(t);
	if (ret != INIT_OK)
		return (init_error(STR_ERR_SEM, t, 1, 0));
	t->pids = malloc(sizeof(pid_t) * t->philo_num);
	if (!t->pids)
		return (init_error(STR_ERR_MALLOC, t, 1, 0));
	memset(t->pids, 0, sizeof(pid_t) * t->philo_num);
	ret = init_philos(t);
	if (ret != INIT_OK)
	{
		if (ret == INIT_ERR_MALLOC)
			return (init_error(STR_ERR_MALLOC, t, 1, 0));
		return (init_error(STR_ERR_SEM, t, 1, 0));
	}
	return (t);
}
