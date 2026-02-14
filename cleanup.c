/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:24:05 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/14 15:52:34 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void     cleanup_table(t_table *t, int forks_inited, int end_inited)
{
    int i;

    if (!t)
        return ;
    if (t->philos)
        free(t->philos);
    if (t->forks)
    {
        i = -1;
        while (++i < forks_inited)
            pthread_mutex_destroy(&t->forks[i].mtx);
        free(t->forks);
    }
    if (end_inited)
        pthread_mutex_destroy(&t->end_mutex);
    t->philos = NULL;
    t->forks = NULL;
}