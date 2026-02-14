
#include "philo.h"

// - if no meals, return ->[0]
// - if only one philo -> ad hoc fucntion 
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

void	print_status(t_status code)
{
	if (code == EAT)
		ft_putstr("Philo is eating.\n", 1);
	else if (code == SLEEP)
		ft_putstr("Philo is sleeping.\n", 1);
	else if (code == THINK)
		ft_putstr("Philo is thinking.\n", 1);
	else if (code == LEFT_FORK)
		ft_putstr("Philo is taking left fork.\n", 1);
	else if (code == RIGHT_FORK)
		ft_putstr("Philo is taking right fork.\n", 1);
	else if (code == DIED)
		ft_putstr("Philo is died.\n", 1);
}

void	only_one_philo(t_table *t)
{	
	usleep(t->t_die);
	print_status(DIED);
	cleanup_table(t, t->philo_num, 0);
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
        if (safe_mutex_handle )

    }



    return (0);
}