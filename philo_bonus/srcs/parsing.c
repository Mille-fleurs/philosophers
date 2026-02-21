/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:48:05 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:37:21 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	only_digit(char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	ft_atoi(const char *str)
{
	long	res;
	int		digit;

	if (!str || !*str)
		return (-1);
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (res > (2147483647 - digit) / 10)
			return (-1);
		res = res * 10 + digit;
		str++;
	}
	return ((int)res);
}

int	is_valid_arg(int ac, char **av)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (++i < ac)
	{
		if (!only_digit(av[i]))
			return (error_msg(STR_ERR_INPUT_DIGIT, av[i], 0));
		res = ft_atoi(av[i]);
		if (res < 0)
			return (error_msg(STR_ERR_INPUT_DIGIT, av[i], 0));
		if (i == 1 && (res < 1 || res > MAX_PHILO))
			return (error_msg(STR_ERR_INPUT_DIGIT, STR_MAX_PHILO, 0));
	}
	return (1);
}

int	parse_arg(t_table *t, int ac, char **av)
{
	int	i;
	int	res;

	t->meal_num = -1;
	i = 0;
	while (++i < ac)
	{
		res = ft_atoi(av[i]);
		if (res < 0)
			return (0);
		if (i == 1)
			t->philo_num = res;
		else if (i == 2)
			t->time_to_die = res;
		else if (i == 3)
			t->time_to_eat = res;
		else if (i == 4)
			t->time_to_sleep = res;
		else if (i == 5)
			t->meal_num = res;
	}
	return (1);
}

