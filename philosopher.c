
#include "philo.h"

// - create all threads, all philos
// - create a monitor thread
// -synchronize the beginning of the simulation
//     pthread_create ->philo starts running.
//     every philo start simultaneously
// -join everyone

void	only_one_philo(t_table *t)
{	
	usleep(t->t_die + 10);
	print_status(1, DIED);
	cleanup_table(t, 1);
}

int		wait_threads_ready(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_num)
	{
		if (!safe_thread_handle(&t->philos[i].thread_id, philosopher, JOIN))
			return (1);
	}
	return (0);
}
// Take forks 
// Eat
// Sleep 
// Think 
// Repeat

// int monitor_end(t_table *t, t_philo *p, t_status code)
// {
// 	if (code == EAT)
// 	{
// 		if (t->meal_num != -1 && t->meal_num == p->meals_eaten)
// 		{
// 			if (set_int())
// 		}
// 	}
// }

int	take_fork(t_table *t, t_philo *p, int p_index)
{
	t_fork f;
	int	f_index;

	if (p_index % 2)
		f_index = p_index;
	else
		f_index = (p_index + 1) % t->philo_num;
	f = t->forks[f_index];
	if (set_int(&f.mtx, &f.taken, 1) == 1)
		return (1);
	if (set_int(&f.mtx, &p->f_num, p->f_num + 1))
		return (1);
	return (0);
}

int eat(t_table *t, t_philo *p, int p_index)
{
	if (p->f_num == 2)
		print_status(p_index, EATING);
	usleep(t->t_eat);


}

void    *philosopher(void *data)
{
    t_philo *p;

    p = (t_philo *)data;
	return (NULL);
}

