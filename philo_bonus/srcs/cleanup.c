/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:46:08 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:37:51 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void    kill_and_wait_children(t_table *t)
{
    int i;
    int status;

    if (!t || !t->pids)
        return ;
    i = -1;
    while (++i < t->philo_num)
    {   
        if (t->pids[i] > 0)
            kill(t->pids[i], SIGKILL);
    }
    i = -1;
    while (++i < t->philo_num)
    {
        if (t->pids[i] > 0)
            waitpid(t->pids[i], &status, 0);
    }
}

static void free_table(t_table *t)
{
    int i;

    if (!t)
        return ;
    if (t->philos)
    {
        i = -1;
        while (++i < t->philo_num)
        {
            if (!t->philos[i])
                continue;
            if (t->philos[i]->sem_meal && t->philos[i]->sem_meal != SEM_FAILED)
                sem_close(t->philos[i]->sem_meal);
            if (t->philos[i]->sem_meal_name)
            {
                sem_unlink(t->philos[i]->sem_meal_name);
                free(t->philos[i]->sem_meal_name);
            }
            free(t->philos[i]);
        }
        free(t->philos);
    }
    free(t->pids);
    free(t);
}

void 	unlink_global_sems(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FULL);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_STOP);
    sem_unlink(SEM_DEATH_LOCK);
}

static void     sem_error_cleanup(t_table *t)
{
    if (t->sem_forks && t->sem_forks != SEM_FAILED)
        sem_close(t->sem_forks);
    if (t->sem_print && t->sem_print != SEM_FAILED)
	    sem_close(t->sem_print);
    if (t->sem_philo_full && t->sem_philo_full != SEM_FAILED)
	    sem_close(t->sem_philo_full);
    if (t->sem_philo_dead && t->sem_philo_dead != SEM_FAILED)
	    sem_close(t->sem_philo_dead);
    if (t->sem_stop && t->sem_stop != SEM_FAILED)
	    sem_close(t->sem_stop);
    if (t->sem_death_lock && t->sem_death_lock != SEM_FAILED)
	    sem_close(t->sem_death_lock);
	unlink_global_sems();
}

void 	cleanup_table(t_table *t, int sem_opened, int children_created)
{
	if (!t)
        return ;
    if (children_created)
        kill_and_wait_children(t);
    if (sem_opened)
        sem_error_cleanup(t);
    free_table(t);
}

