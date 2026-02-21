

#include "philo_bonus.h"

static void    kill_philos(t_table *t, int exit_code)
{
    unsigned int    i;

    i = 0;
    while (i < t->philo_num)
    {
        kill(t->philos[i], SIGKILL);
        i++;
    }
    return (exit_code);
}
