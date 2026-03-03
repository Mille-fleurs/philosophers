/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:47:55 by chitoupa          #+#    #+#             */
/*   Updated: 2026/03/03 14:14:42 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, t_status code)
{
	long	time;

	sem_wait(philo->sem_print);
	time = get_current_time() - philo->table->start_time;
	if (time < 0)
		time = 0;
	if (code == EATING)
		printf("%ld %d is eating\n", time, philo->id);
	else if (code == SLEEPING)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (code == THINKING)
		printf("%ld %d is thinking\n", time, philo->id);
	else if (code == GOT_FORK_1 || code == GOT_FORK_2)
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if (code == DIED)
	{
		printf("%ld %d died\n", time, philo->id);
		sem_post(philo->sem_print);
		return ;
	}
	sem_post(philo->sem_print);
}
