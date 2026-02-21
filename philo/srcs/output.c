

#include "philo.h"

void	print_status(t_table *t, int p_index, t_status code)
{
	long long	time;

	if (!safe_mutex_handle(&t->print_mutex, LOCK))
		return (end_on_error(t));
	if (!simulation_finished(t) || code == DIED)
	{
		time = (long long)(get_current_time() - t->start_time);
		if (code == EATING)
			printf("%lld %d is eating\n", time, p_index);
		else if (code == SLEEPING)
			printf("%lld %d is sleeping\n", time, p_index);
		else if (code == THINKING)
			printf("%lld %d is thinking\n", time, p_index);
		else if (code == GOT_FORK_1 || code == GOT_FORK_2)
			printf("%lld %d has taken a fork\n", time, p_index);
		else if (code == DIED)
			printf("%lld %d died\n", time, p_index);
	}
	if (!safe_mutex_handle(&t->print_mutex, UNLOCK))
		return (end_on_error(t));
}

// # define NC		"\e[0m"
// # define RED	"\e[31m"
// # define GREEN	"\e[32m"
// # define PURPLE	"\e[35m"
// # define CYAN	"\e[36m"

// static void	print_status_debug(t_philo *philo, char *color,
// 								char *str, t_status status)
// {
// 	if (status == GOT_FORK_1)
// 		printf("[%10ld]\t%s%03d\t%s\e[0m: fork [%d]\n",
// 			get_time_in_ms() - philo->table->start_time,
// 			color, philo->id + 1, str, philo->first_f);
// 	else if (status == GOT_FORK_2)
// 		printf("[%10ld]\t%s%03d\t%s\e[0m: fork [%d]\n",
// 			get_time_in_ms() - philo->table->start_time,
// 			color, philo->id + 1, str, philo->second_f);
// 	else
// 		printf("[%10ld]\t%s%03d\t%s\e[0m\n",
// 			get_time_in_ms() - philo->table->start_time,
// 			color, philo->id + 1, str);
// }

// void	print_status_(t_philo *philo, t_status status)
// {
// 	if (status == DIED)
// 		print_status_debug(philo, RED, "died", status);
// 	else if (status == EATING)
// 		print_status_debug(philo, GREEN, "is eating", status);
// 	else if (status == SLEEPING)
// 		print_status_debug(philo, CYAN, "is sleeping", status);
// 	else if (status == THINKING)
// 		print_status_debug(philo, CYAN, "is thinking", status);
// 	else if (status == GOT_FORK_1)
// 		print_status_debug(philo, PURPLE, "has taken a fork", status);
// 	else if (status == GOT_FORK_2)
// 		print_status_debug(philo, PURPLE, "has taken a fork", status);
// }