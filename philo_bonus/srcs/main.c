/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:47:35 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:37:24 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_table	*table;
	int ret;

	table = NULL;
	ret = 0;
	if (ac != 5 && ac != 6)
		return (error_msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!is_valid_arg(ac, av))
		return (EXIT_FAILURE);
	table = init_table(ac, av, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	if (!stop_simulation(table))
		return (cleanup_table(table, EXIT_FAILURE));
	return (cleanup_table(table, EXIT_SUCCESS));
}

