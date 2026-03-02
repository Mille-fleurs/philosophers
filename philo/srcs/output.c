
#include "philo.h"

void	print_status(t_table *t, int p_index, t_status code)
{
	long long	time;

	safe_mutex_handle(&t->print_mutex, LOCK);
	if (!simulation_finished(t) || code == DIED)
	{
		time = (long long)(get_current_time() - t->start_time);
		if (time < 0)
			time = 0;
		if (code == EATING)
			printf("%lld %d is eating\n", time, p_index);
		else if (code == SLEEPING)
			printf("%lld %d is sleeping\n", time, p_index);
		else if (code == THINKING)
			printf("%lld %d is thinking\n", time, p_index);
		else if (code == GOT_FORK_1 || code == GOT_FORK_2)
			printf("%lld %d has taken a fork\n", time, p_index);
		else if (code == DIED)
		{
			printf("%lld %d died\n", time, p_index);
			safe_mutex_handle(&t->print_mutex, UNLOCK);
			return ;
		}
	}
	safe_mutex_handle(&t->print_mutex, UNLOCK);
}
