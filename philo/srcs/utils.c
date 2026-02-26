/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:01:43 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/26 13:53:46 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	precise_sleep(t_table *t, long ms)
{
	long	start;

	start = get_current_time();
	while (!simulation_finished(t))
	{
		if ((get_current_time() - start) <= ms)
			break ;
		usleep(200);
	}
}

// void	*safe_malloc(size_t bytes)
// {
// 	void	*ret;

// 	ret = malloc(bytes);
// 	if (!ret)
// 		return (NULL);
// 	return (ret);
// }
