
#include "philo_bonus.h"

void *free_table(t_table *t)
{
    unsigned int i;

    if (!t)
        return (NULL);
    if (t->philos != NULL)
    {
        i = 0;
        while (i < t->philo_num)
        {
            if (t->philos[i] != NULL)
            {
                if (t->philos[i]->sem_meal_name)
                    free(t->philos[i]->sem_meal_name);
                free(t->philos[i]);
            }
            i++;
        }
        free(t->philos);
    }
    if (t->pids)
        free(t->pids);
    free(t);
    return (NULL);
}

void 	unlink_grobal_sems(t_table *t)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FULL);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_STOP);
}

int     sem_error_cleanup(t_table *t)
{
    sem_close(t->sem_forks);
	sem_clone(t->sem_print);
	sem_close(t->sem_philo_full);
	sem_close(t->sem_philo_dead);
	sem_close(t->sem_stop);
	unlink_global_sems(t);
}

int 	cleanup_table(t_table *t, int exit_code)
{
	if (!t)
		return ;
	pthread_join(t->meal_monitor, NULL);
	pthread_join(t->death_monitor, NULL);
	sem_close(t->sem_forks);
	sem_clone(t->sem_print);
	sem_close(t->sem_philo_full);
	sem_close(t->sem_philo_dead);
	sem_close(t->sem_stop);
	unlink_global_sems(t);
	free_table(t);
    return (exit_code);
}
