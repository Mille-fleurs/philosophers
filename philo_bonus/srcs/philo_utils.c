
#include "philo_bonus.h"

void    set_stop(t_philo *p, int code)
{
    sem_wait(p->sem_meal);
    if (!p->stop)
    {
        p->stop = 1;
        p->exit_code = code;
    }
    sem_post(p->sem_meal);
}

int     get_stop(t_philo *p)
{
    int ret;

    sem_wait(p->sem_meal);
    ret = p->stop;
    sem_post(p->sem_meal);
    return (ret);
}

int     take_forks(t_philo *p)
{
    sem_wait(p->sem_forks);
    sem_wait(p->sem_meal);
    p->forks_held = 1;
    sem_post(p->sem_meal);
    print_status(p, GOT_FORK_1);
    if (get_stop(p))
    {
        sem_post(p->sem_forks);
        return (0);
    }
    sem_wait(p->sem_forks);
    print_status(p, GOT_FORK_2);
    if (get_stop(p))
    {
        drop_forks(p);
        return (0);
    }
    sem_wait(p->sem_meal);
    p->forks_held = 2;
    sem_post(p->sem_meal);
    return (1);
}

void    drop_forks(t_philo *p)
{
    int held;

    sem_wait(p->sem_meal);
    held = p->forks_held;
    p->forks_held = 0;
    sem_post(p->sem_meal);
    while (held-- > 0)
        sem_post(p->sem_forks);
}

void start_monitor(t_philo *p)
{
    if (pthread_create(&p->personal_monitor, NULL, personal_monitor, p) != 0)
    {
        p->exit_code = CHILD_EXIt_ERR_PTHREAD;
        set_stop(p, p->exit_code);
    }
    else
        pthread_detach(p->personal_monitor);
}