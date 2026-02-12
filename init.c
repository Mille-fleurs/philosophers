
#include "philo.h"

// pthread_t	*init_threads(int nums)
// {
// 	int		id;
// 	t_philo	p;
// 	int		i;

// 	i = 0;
// 	while (i < nums)
// 	{
// 		p.id = i + 1;
// 	}
// }

	// int	id; //1..N
	// int count;
	// t_fork	*l_fork;
	// t_fork	*r_fork;
	// long long last_meal_time;
	// pthread_t	thread_id;
	// t_table	*table;

// void	init_fork(t_table *t)
// {
// 	t_fork *f;
// 	int	i;

// 	i = -1;
// 	while (++i < t->philo_num)
// 	{
// 		if (pthread_mutex_init()
// 	}
// } 

// void	init_philo(t_table *t)
// {
//     int i;
//     t_philo *p;

//     i = -1;
//     while (++i < t->philo_num)
//     {
// 		p->id = i + 1;
// 		p->count = 0;
// 		p->l_fork = 
//     }
 

// }

int	init_table(t_table *t, int ac, char **av)
{
	int error;
    int i;

	error = 0;
	t->philo_num = ft_atoi(av[1], &error);
	t->t_die = ft_atoi(av[2], &error);
	t->t_eat = ft_atoi(av[3], &error);
	t->t_sleep = ft_atoi(av[4], &error);
	if (ac == 6 && check_brakets(av[5]))
		t->meal_num = ft_atoi(av[5], &error);
	else
		t->meal_num = -1;
	t->start_time = get_current_time();
	t->forks = safe_malloc(t->philo_num * sizeof(t_fork));
	t->philos = safe_malloc(t->philo_num * sizeof(t_philo));
    i = -1;
    while (++i < t->philo_num)
    {
        safe_mutex_handle(&t->forks[i].mutex, INIT);
        t->forks[i].fork_id = i;
    }
	return (1);
}
