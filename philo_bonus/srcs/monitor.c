/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:47:44 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:36:55 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int    kill_philos(t_table *t, int exit_code)
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

void	*personal_death_monitor(void *data)
{
    t_philo *p;
    time_t  lm_time;
    int eaten;

    p = (t_philo *)data;
    lm_time = get_time_ms(p->sem_meal, &p->last_meal_time);
    if (lm_time == -1)
    {
        cleanup_table(p->table, 0);
        return ;
    }
    if (get_current_time() - lm_time >= p->table->time_to_die)
    {
        
    }
    eaten = get_int(p->sem_meal, &p->meals_eaten);
    if (eaten != -1 && eaten == p->table->meal_num)
    {
        set_int(p->table->sem_stop, &p->table->sim_stop);

    }


}



// void    *meal_monitor(void *data);
// void    *death_monitor(void *data);

/*
1) What each monitor is responsible for

A) philo->personal_dead (inside each philosopher process)
Role: local watchdog for this philosopher only.
Runs in the philosopher child process.
Periodically checks: now - last_meal >= time_to_die.
Also checks “ate enough” and, once, notifies the global counter.
If it detects death:
prints died (protected by print semaphore),
signals one global “death happened” semaphore (sem_philo_dead),
then it can stop (the global monitor will kill everyone).
Key rule: it must read last_meal under a per-philo protection semaphore/mutex (sem_meal) to avoid races with the eating routine that updates last_meal.

B) table->death_monitor (parent process)
Role: global reaper for death.
Runs in the parent process only.
Waits on sem_philo_dead.
As soon as it unblocks (first death):
sets a shared “stop” flag (protected by sem_stop),
kills all philosopher PIDs (SIGKILL or SIGTERM then SIGKILL),
unblocks/flushes other waits if needed (e.g., sem_philo_full) so nothing deadlocks.
Key rule: only one death is enough to end the whole simulation.

C) table->meal_monitor (parent process)
Role: global reaper for “everyone ate enough”.
Runs in the parent process only.
Only enabled if must_eat_count > 0 (and usually nb_philos > 1).
Waits nb_philos times on sem_philo_full.
Each philosopher posts exactly once when it reaches the target.
When count reaches nb_philos:
sets stop flag (protected by sem_stop),
kills all philosopher PIDs,
signals sem_philo_dead or similar to release the death monitor if it is blocked.
Key rule: each philosopher must have a boolean like ate_enough to avoid posting sem_philo_full multiple times.

2) Minimal “how to wire it” (no code, just steps)

Parent creates named semaphores:
sem_stop (binary) to protect stop_sim
sem_print (binary) to serialize output
sem_philo_dead (starts at 0) global event: “someone died”
sem_philo_full (starts at 0) global counter: “a philosopher reached must_eat”
plus per-philo sem_meal (binary) to protect last_meal / times_ate
Parent forks all philosophers, stores PIDs in table->pids[].

In each child:
initialize last_meal = start_time (or “now” after start delay),
start philo->personal_dead thread,
run the philosopher routine (eat/sleep/think loop),
when eating: update last_meal and times_ate under sem_meal.

In parent:
start table->death_monitor thread (waits sem_philo_dead)
start table->meal_monitor thread (waits sem_philo_full nb_philos times, only if must_eat_count enabled)

Stopping rule:
both global monitors, before killing, take sem_stop, set stop_sim = true, release sem_stop.
children should periodically check stop_sim only if it is shared memory; otherwise they simply get killed (common in bonus).

3) The 3 practical pitfalls to avoid

Race on last_meal: always guard reads/writes with sem_meal (your pasted code does this).
Posting sem_philo_full multiple times: use ate_enough boolean; post only the first time times_ate == must_eat_count.
Deadlock on stop: when one global monitor triggers stop, it should “wake” the other monitor if that other one could be blocked forever (that’s why they sometimes sem_post(sem_philo_dead) or sem_post(sem_philo_full) after killing).
*/