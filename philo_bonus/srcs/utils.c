/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:43:30 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:36:47 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_utoa(unsigned int n)
{
	char *res;
	size_t		len;
	unsigned int temp;

	temp = n;
	len = (n == 0);
	while (temp > 0)
	{
		len++;
		temp /= 10;
	}
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len--)
	{
		res[len] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}

void	unblock_monitor_threads(t_table *t)
{
	int i;

	sem_post(t->sem_philo_dead);
	i = -1;
	while (++i < t->philo_num)
		sem_post(t->sem_philo_full);
}

void	join_monitor_threads(t_table *t)
{
	if (t->meal_num != -1)
		pthread_join(t->meal_monitor, NULL);
	pthread_join(t->death_monitor, NULL);
}
