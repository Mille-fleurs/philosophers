
# Philosophers

*This project has been created as part of the 42 curriculum by chitoupa*

---

## Description

The **Philosophers** project is an introduction to concurrent programming. 
It is based on Edsger Dijkstra’s classic Dining Philosophers problem.
The objective is to simulate philosophers sitting at a round table who alternate between:

* Eating
* Sleeping
* Thinking

Each philosopher needs two forks to eat. The challenge is to design a synchronization strategy that:

* Prevents race conditions
* Avoids deadlocks
* Avoids starvation
* Ensures proper program termination

Two implementations are required:

* **Mandatory part**: Threads and mutexes
* **Bonus part**: Processes and semaphores

The simulation stops when:

* A philosopher dies (fails to eat before `time_to_die`)
* Or all philosophers have eaten a specified number of times (optional argument)

---

## Program Arguments

Both programs take the following arguments:

./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep [number_of_times_each_philosopher_must_eat]


* `number_of_philosophers` — Number of philosophers and forks
* `time_to_die` — Time in ms before a philosopher dies without eating
* `time_to_eat` — Time in ms spent eating
* `time_to_sleep` — Time in ms spent sleeping
* `number_of_times_each_philosopher_must_eat` — Optional. Simulation stops if all philosophers eat this many times

All values must be positive integers within `INT_MAX`.

---

## Output Format

Each action is printed as:

```
[timestamp] [philosopher_id] has taken a fork
[timestamp] [philosopher_id] is eating
[timestamp] [philosopher_id] is sleeping
[timestamp] [philosopher_id] is thinking
[timestamp] [philosopher_id] died
```

* Timestamp is in milliseconds since simulation start
* No additional output is allowed
* Output must not interleave incorrectly

---

# Mandatory Part — Threads and Mutexes

In this version:

* Each philosopher is a thread
* Each fork is protected by a `pthread_mutex_t`
* Shared state is protected using additional mutexes
* A monitor thread detects death and simulation stop

### Synchronization Strategy

* Fork ordering is used to prevent deadlocks
* Shared variables are protected with mutexes
* The simulation end flag is protected
* No busy waiting

---

# Bonus Part — Processes and Semaphores

In this version:

* Each philosopher is a process
* Forks are implemented as a counting semaphore
* Additional semaphores are used for:

  * Printing synchronization
  * Death event signaling
  * Meal completion detection
  * Global stop signal

A parent process monitors:

* Death events
* Meal completion events

When a stop condition occurs:

* All child processes are killed
* Resources are cleaned properly

---

### Mandatory

```
cd philo
make
```

### Bonus

```
cd philo_bonus
make
```

---

## Execution Examples

```
./philo 5 800 200 200
```

```
./philo_bonus 5 800 200 200 7
```

---

## Technical Choices

* Strict mutex protection for shared variables
* Dedicated monitoring logic
* Structured error handling and cleanup
* No memory leaks
* No data races

---

## Resources

* 42 Philosophers Subject
* POSIX Threads (pthreads) documentation
* POSIX Semaphores documentation
* `man pthread_create`
* `man sem_open`

### AI Usage

AI tools were used for:

* Clarifying concurrency concepts
* Reviewing synchronization logic
* Improving structure and readability of documentation

All implementation decisions and final code structure were written and validated manually.

---

## Project Structure

```
philo/
    include/
        philo.h
    srcs/
        main.c
        init.c
        output.c
        monitor.c
        parsing.c
        philo.c
        philo_utils.c
        safe_handle.c
        set_get.c
        utils.c
        error.c
    Makefile

philo_bonus/
    include/
        philo_bonus.h
    srcs/
        main.c
        init.c
        monitor.c
        output.c
        parsing.c
        cleanup.c
        exit.c
        debug.c
        philo.c
        philo_utils.c
        set_get.c
        time.c
        utils.c
    Makefile

```

---

## Author

ctoupa

