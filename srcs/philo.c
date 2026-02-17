
#include "philo.h"

// - create all threads, all philos
// - create a monitor thread
// -synchronize the beginning of the simulation
//     pthread_create ->philo starts running.
//     every philo start simultaneously
// -join everyone

void	only_one_philo(t_table *t)
{	
	ft_usleep((t->t_die + 10));
	print_status(t, 1, DIED);
	cleanup_table(t, 1);
}

// Take forks 
// Eat
// Sleep 
// Think 
// Repeat

// int	take_fork(t_table *t, t_philo *p, int p_index)
// {
// 	t_fork f;
// 	int	f_index;

// 	if (p_index % 2)
// 		f_index = p_index;
// 	else
// 		f_index = (p_index + 1) % t->philo_num;
// 	f = t->forks[f_index];
// 	if (set_int(&f.mutex, &f.taken, 1) == 1)
// 		return (1);
// 	if (set_int(&f.mutex, &p->f_num, p->f_num + 1))
// 		return (1);
// 	return (0);
// }

// void sleep_routine(t_table *t)
// {

// }

// int eat_routine(t_table *t, t_philo *p, int p_index)
// {
// 	if (p->f_num == 2)
// 		print_status(p_index, EATING);
// 	usleep(t->t_eat);


// }

int	think_routine(t_table *t)
{
	int t_think;

	

}

void    *philosopher(void *data)
{
    t_philo *p;

    p = (t_philo *)data;
	printf("philo_id: %d\n", p->id);
	printf("current_time: %ld\n", get_current_time());
	print_status(p->table, p->id, THINKING);
	return (NULL);
}
