
#include "philo.h"

int		unlock_forks_return(t_philo *p, int must_set)
{
	unlock_forks_end(p, must_set);
	return (0);
}

void	end_on_error(t_table *t)
{
	set_int(&t->end_mutex, &t->end, 1);
}

void	only_one_philo(t_table *t)
{	
   	print_status(t, t->philos[0].id, GOT_FORK_1);
	precise_sleep(t, t->time_die);
	print_status(t, 1, DIED);
	set_int(&t->end_mutex, &t->end, 1);
}

int	wait_until_ready(t_table *t)
{
	int ready;

	ready = -1;

	while (1)
	{
		ready = get_int(&t->table_mutex, &t->threads_ready);
		if (ready < 0)
			return (end_on_error(t), 0);
		if (ready == 1)
			break;
		precise_sleep(t, 1);
	}
	return (1);
}

int preparation(t_table *t)
{
	if (!wait_until_ready(t))
	{
		set_int(&t->end_mutex, &t->end, 1);
		return (0);
	}
	while (!simulation_finished(t) && get_current_time() < t->start_time)
		precise_sleep(t, 1);
	return (1);
}
