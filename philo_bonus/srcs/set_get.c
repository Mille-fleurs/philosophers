#include "philo_bonus.h"

int	set_int(sem_t *lock, int *dest, int value)
{
	if (sem_wait(lock) == -1)
        return (0);
	*dest = value;
	if (sem_post(lock) == -1)
        return (0);
	return (1);
}

int	get_int(sem_t *lock, int *src)
{
	int	ret;

	if (sem_wait(lock) == -1)
        return (-1);
	ret = *src;
	if (sem_post(lock) == -1)
        return (-1);
	return (ret);
}

int	set_long(sem_t *lock, long *dest, long value)
{
	if (sem_wait(lock) == -1)
        return (0);
	*dest = value;
	if (sem_post(lock) == -1)
        return (0);
	return (1);
}

time_t	get_time_ms(sem_t *lock, long *src)
{
	long	ret;

	if (sem_wait(lock) == -1)
        return (-1);
	ret = *src;
	if (sem_post(lock) == -1)
        return (-1);
	return (ret);
}

int		simulation_finihsed(t_table *t)
{
	int	ret;

	sem_wait(t->sem_stop);
	ret = t->sim_stop;
	sem_post(t->sem_stop);
	return (ret);
}

