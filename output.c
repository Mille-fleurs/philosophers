/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:54:18 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/15 21:07:40 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(long long start, int p_index, t_status code)
{
    long long time;

    time = get_current_time() - start;
	if (code == EATING)
		printf("%ld %d is eating\n", time, p_index);
	else if (code == SLEEPING)
		printf("%ld %d is sleeping\n", time, p_index);
	else if (code == THINKING)
		printf("%ld %d is thinking\n", time, p_index);
	else if (code == GOT_FORK_1 || code == GOT_FORK_2)
		printf("%ld %d has taken a fork\n", time, p_index);
	else if (code == DIED)
		printf("%ld %d died\n", time, p_index);
}
