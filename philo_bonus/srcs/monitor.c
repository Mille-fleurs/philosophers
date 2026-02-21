/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 21:47:44 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/21 23:36:55 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void    kill_philos(t_table *t, int exit_code)
{
    unsigned int    i;

    i = 0;
    while (i < t->philo_num)
    {
        kill(t->philos[i], SIGKILL);
        i++;
    }
    return (exit_code);
}
