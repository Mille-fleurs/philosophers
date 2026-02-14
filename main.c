/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:51:46 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/14 20:13:56 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_usage(void)
{
	write(1, ERR_USAGE, 2);
}

int	error_msg(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

int	main(int ac, char **av)
{
	int		error;
	t_table	t;

	if (ac != 5 || ac != 6)
		return (print_usage());
	if (!init_table(&t, ac, av))
		return (1);
	return (0);
}

// dinner_start
// end with no leak -> philos full | | 1 philo died
