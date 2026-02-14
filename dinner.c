
#include "philo.h"

// - create all threads, all philos
// - create a monitor thread
// -synchronize the beginning of the simulation
//     pthread_create ->philo starts running.
//     every philo start simultaneously
// -join everyone

typedef struct s_fork
{
	pthread_mutex_t mtx;
	int	id;
}				t_fork;

typedef	struct	s_philo
{
	int	id; //1..N
	int is_full;
	int	meals_eaten;
	t_fork	*first_f;
	t_fork	*second_f;
	long long last_meal_time;
	pthread_t	thread_id;
	t_table	*table;
}				t_philo;

typedef struct s_table
{
	int philo_num;
	int t_die;
	int	t_eat;
	int	t_sleep;
	int meal_num; //FLAG if -1
	int	end; //someone died or ate enoughS
	int all_ready;
	long long start_time;
	pthread_mutex_t table_mutex;
	pthread_mutex_t	end_mutex;
	t_fork	*forks;
	t_philo	*philos;
}				t_table;

typedef enum s_op
{
	LOCK,
	UNLOCK,
	CREATE,
	INIT,
	DESTROY,
	JOIN,
	DETACH,
}			t_op;

typedef enum s_status
{
	EAT,
	SLEEP,
	THINK,
	LEFT_FORK,
	RIGHT_FORK,
	DIED
}			t_status;

void	ft_purstr(char *s, int fd)
{
	while (*s)
	{
		write(fd, &s, 1);
		s++;
	}
}

void	print_status(int p_index, t_status code)
{
	if (code == EAT)
		printf("%d is eating\n", p_index);
	else if (code == SLEEP)
		printf("%d is sleeping\n", p_index);
	else if (code == THINK)
		printf("%d is thinking\n", p_index);
	else if (code == LEFT_FORK)
		printf("%d has taken a fork\n", p_index);
	else if (code == RIGHT_FORK)
		printf("%d is taken a fork\n", p_index);
	else if (code == DIED)
		printf("%d died\n", p_index);
}

void	only_one_philo(t_table *t)
{	
	usleep(t->t_die);
	print_status(1, DIED);
	cleanup_table(t, t->philo_num, 0);
}

int		wait_all_thread(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_num)
	{
		if (safe_thread_handle(&t->philos[i].thread_id, dinner_simulation, JOIN) == 1)
			return (1);
		
	}
}
// Take forks 
// Eat
// Sleep 
// Think 
// Repeat

int	take_fork(t_table *t, int p_index)
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
	return (0);
}

void    *dinner_simulation(void *data)
{
    t_philo *p;

    p = (t_philo *)data;








    return (NULL);
}

int    dinner_start(t_table *t)
{
    int     i;

    i = -1;
    while (++i < t->philo_num)
    {
        if (safe_thread_handle(&t->philos[i].thread_id, dinner_simulation, &t->philos[i], CREATE) == 1)
            return (1);
    }
    t->start_time = get_currnt_time();
    i = -1;
    while (++i < t->philo_num)
    {
        if (safe_mutex_handle(&t->forks[i].mtx, INIT) == 1)
			return (1);
	}
    return (0);
}