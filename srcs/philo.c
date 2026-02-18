
#include "philo.h"

// - create all threads, all philos
// - create a monitor thread
// -synchronize the beginning of the simulation
//     pthread_create ->philo starts running.
//     every philo start simultaneously
// -join everyone

void	only_one_philo(t_table *t)
{	
	ft_usleep((t->time_die + 10));
	print_status(t, 1, DIED);
	cleanup_table(t, 1, 1);
}

void	end_on_error(t_table *t)
{
	set_int(&t->end_mutex, &t->end, 1);
}

int	take_fork(t_philo *p)
{
	if (safe_mutex_handle(&p->first_f->mutex, LOCK) == 0)
		return (end_on_error(p->table), 0);
	if (!simulation_finished(p->table))
		print_status(p->table, p->id, GOT_FORK_1);
	if (safe_mutex_handle(&p->second_f->mutex, LOCK) == 0)
	{
		safe_mutex_handle(&p->first_f->mutex, UNLOCK);
		return (end_on_error(p->table), 0);
	}
	if (!simulation_finished(p->table))
		print_status(p->table, p->id, GOT_FORK_2);
	return (1);
}

void	think_routine(t_philo *p, int silent)
{
	long	time_to_think;
	long	last_meal_time;

	last_meal_time = get_long(&p->philo_mutex, &p->last_meal_time);
	if (last_meal_time == -1)
	{
		set_int(&p->table->end_mutex, &p->table->end, 1);
		return ;
	}
	time_to_think = (p->table->time_die - (get_current_time() - last_meal_time) - p->table->time_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (!simulation_finished(p->table) && silent == 0)
		print_status(p->table, p->id, THINKING);
	pricise_sleep(p->table, time_to_think);
}

void    *philosopher(void *data)
{
    t_philo *p;

    p = (t_philo *)data;

	while (!get_int(&p->table->table_mutex, &p->table->threads_ready))
		usleep(100);
	while (get_current_time() < p->table->start_time)
		usleep(100);
	print_status(p->table, p->id, THINKING);
	while (!simulation_finished(p->table))
	{
		think_routine(p, 0);
		usleep(1000);
	}
	return (NULL);
}
