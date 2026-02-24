/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:48:23 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:37:13 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


/*
1) eat_sleep_routine(philo) — what it must do (order matters)

Take two forks
Call your “take fork” action twice.
Internally this usually means sem_wait(sem_forks) twice (or one helper that does that).
Print “has taken a fork” each time (subject expects a line per fork).
Print EATING
Print status after you own both forks.
Update last_meal at the start of eating
Lock the “meal” protection semaphore/mutex (e.g. sem_meal).
Set philo->last_meal = now_in_ms().
Unlock sem_meal.
This is important: record at the beginning, not the end.
Eat for time_to_eat
Use your precise sleep (looped usleep, or similar) so you do not drift too much.
Print SLEEPING
Immediately after eating time ends.
Release the two forks
sem_post(sem_forks) twice.
Update counters safely
Lock sem_meal (or a dedicated semaphore for counters).
Decrease “forks held” by 2 if you track it (optional but useful for debugging).
Increment times_ate.
Unlock.
Sleep for time_to_sleep
Call your precise sleep.
That’s the minimal “atomic” routine: acquire resources → mark meal start → eat → release → update counters → sleep.

2) think_routine(philo, silent) — what it must do and why

Compute a think delay based on hunger window
Lock sem_meal.
Compute:
remaining life time until death if no meal happens:
remaining = time_to_die - (now - last_meal)
subtract the time you’ll spend eating next:
time_to_think = (remaining - time_to_eat) / 2
Unlock sem_meal.
Clamp it to sane bounds
If negative: set to 0.
If silent == true and it becomes 0: force 1ms (micro-stagger so everyone doesn’t align perfectly).
Optional cap (like 200ms) to avoid huge think times that reduce responsiveness / fairness.
Print THINKING only if not silent
Silent is used when you want to delay without spamming output (common for initial staggering).
Sleep for time_to_think
Use the same precise sleep.
Purpose: avoid everyone competing for forks at the exact same rhythm, which reduces contention and helps fairness.

3) lone_philo_routine(philo) — the special case you must handle

When nb_philos == 1:
Ensure start synchronization is respected (wait until start_time).
If must_eat_count == 0, exit “full” immediately.
Print one “has taken a fork”.
Sleep exactly time_to_die.
Print “died”.
Exit cleanly (free/close semaphores if your design requires it).
Why separate routine: with one philosopher, attempting to acquire “two forks” would block forever, so you must explicitly model the subject behavior.

4) philosopher_routine(philo) — the infinite loop

Optional initial staggering:
If id is odd/even (your choice), call think_routine(philo, true) once.
The goal: offset half of the philosophers slightly so they don’t deadlock / stampede semaphores simultaneously.

Loop forever:
eat_sleep_routine(philo)
think_routine(philo, false)
Stop condition is usually handled by:
a monitor thread inside each child process, or
the parent killing children on death/full,
so the loop itself often stays while (1).

5) philosopher(table) — the child process entrypoint checklist

In the child process, do this in this order:
Get philo = table->this_philo (or passed-in philo pointer).
If nb_philos == 1: run lone_philo_routine(philo) and exit.
Initialize IPC/semaphores for this child (open named semaphores, set pointers).

Handle trivial exits:
If must_eat_count == 0: signal “full” and exit.
If time_to_die == 0: signal “dead” and exit.
Initialize last_meal = start_time protected by sem_meal.
Wait until the global start_time (barrier-like delay).
Enter philosopher_routine(philo).
That gives you the same structure/behavior as the reference: correct ordering, correct timing semantics, safe shared updates, and clean special-case handling.
*/