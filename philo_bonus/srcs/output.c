

#include "philo_bonus.h"

void	print_status(t_philo *philo, int sim_finished, t_status code)
{
    time_t time;

	if (!sim_finished)
		sem_wait(philo->sem_print);
	if (!sim_finished|| code == DIED)
	{
    	time = (long long)(get_current_time() - philo->table->start_time);
		if (code == EATING)
			printf("%lld %d is eating\n", time, philo->id + 1);
		else if (code == SLEEPING)
			printf("%lld %d is sleeping\n", time, philo->id + 1);
		else if (code == THINKING)
			printf("%lld %d is thinking\n", time, philo->id + 1);
		else if (code == GOT_FORK_1 || code == GOT_FORK_2)
			printf("%lld %d has taken a fork\n", time, philo->id + 1);
		else if (code == DIED)
			printf("%lld %d died\n", time, philo->id + 1);
	}
	if (!sim_finished)
		sem_post(philo->sem_print);
}

