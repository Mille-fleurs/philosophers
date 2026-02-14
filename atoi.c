/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:30:02 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/14 15:53:01 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_error(int *error)
{
	if (error && !*error)
		*error = 1;
	return (0);
}

int	ft_atoi(const char *str, int *error)
{
	long result;
	int has_digit;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (set_error(error));
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0' || !has_digit)
		return (set_error(error));
	return ((int)result);
}
