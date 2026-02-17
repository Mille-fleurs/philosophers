/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:30:02 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/17 22:06:04 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	only_digit(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(const char *str, int *of)
{
	long	res;
	int		digit;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		res = res * 10 + digit;
		if (res > (2147483648 - digit) / 10)
		{
			*of = 1;
			return (0);
		}
		str++;
	}
	return ((int)res);
}

int	is_valid_arg(int ac, char **av)
{
	int	of;
	int res;
	int i;

	of = 0;
	res = 0;
	i = -1;
	while (++i < ac)
	{
		if (!only_digit(av[i]))
			return (error_msg(STR_ERR_INPUT_DIGIT, av[i], 0));
		res = ft_atoi(av[i], &of);
		if (i == 1 && (res < 1 || res > MAX_PHILO))
			return (error_msg(STR_ERR_INPUT_DIGIT, STR_MAX_PHILO, 0));
		if ((i >= 2 && i <= 5) && (res < 0 || of == 1))
			return (error_msg(STR_ERR_INPUT_DIGIT, av[i], 0));
	}
	return (1);
}

