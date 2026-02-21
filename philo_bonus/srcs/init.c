
#include "philo_bonus.h"

// Allocate and fill t_table from argv
// Create/open global named semaphores
// Allocate and initialize table->philos array
// Prepare per-philo unique name sem_meal_name (but open sem_meal later in the child)

static int open_global_sems(t_table *t, int i)
{
	t->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0644, t->philo_num);
	t->sem_print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	t->sem_philo_full = sem_open(SEM_FULL, O_CREAT, 0644, t->philo_num);
	t->sem_philo_dead = sem_open(SEM_DEAD, O_CREAT, 0644, t->philo_num);
	t->sem_stop = sem_open(SEM_STOP, O_CREAT, 0644, 1);
	if (t->sem_forks == SEM_FAILED || t->sem_print == SEM_FAILED || t->sem_philo_full == SEM_FAILED
		|| t->sem_philo_dead == SEM_FAILED || t->sem_stop == SEM_FAILED)
	{
		error_msg(STR_ERR_SEM, NULL, 0);
		
		
	
	}
}

static char	*make_sem_meal_name(unsigned int id)
{

}

static bool	init_philos(t_table *t)
{

}

t_table *init_table(int ac, char **av, int i)
{
	t_table *t;
	
	t = malloc(sizeof(*t));
	if (!t)
		return (NULL);
	memset(t, 0, sizeof(*t));
	if (!parse_arg(t, ac, av))
		return (free(t), NULL);
	if (!init_table_mutexes(t))
		return (cleanup_table(t, 0, 0), NULL);
	if (!init_fork(t, &forks_inited))
		return (cleanup_table(t, forks_inited, 0), NULL);
	if (!init_philo(t, &philos_inited))
		return (cleanup_table(t, forks_inited, philos_inited), NULL);
	return (t);
}

// What NOT to do in init.c (to avoid bugs)
// Do not fork() in init (keep init purely “setup”).
// Do not open sem_meal in parent unless you have a reason.
// Best practice: open it in the child after fork:
// sem_unlink(p->sem_meal_name) (optional but clean)
// p->sem_meal = sem_open(p->sem_meal_name, O_CREAT, 0644, 1)
// Do not store “fork objects” in bonus. Only sem_forks counter exists.
// 4) Quick checklist: init is correct if…
// Running twice does not break semaphores (because of unlink).
// SEM_FORKS initial value = N.
// SEM_PRINT initial value = 1.
// SEM_FULL and SEM_DEAD initial value = N (for event strategy).
// Every philo has a unique sem_meal_name like /philo_local_meal_1, /..._2, etc.
// On any error, you do not leak:
// sem_meal_name strings
// table->philos
// global semaphores
