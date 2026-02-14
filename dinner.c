
#include "philo.h"

// - if no meals, return ->[0]
// - if only one philo -> ad hoc fucntion 
// - create all threads, all philos
// - create a monitor thread
// -synchronize the beginning of the simulation
//     pthread_create ->philo starts running.
//     every philo start simultaneously
// -join everyone

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
    return (0);
}