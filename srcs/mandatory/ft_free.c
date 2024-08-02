/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:23:47 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/01 22:34:48 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	ft_mutexes_clean(t_program *prog)
{
	int		i;

	i = 0;
	if (prog->mt_forks)
	{
		while (i < prog->philo_count)
		{
			pthread_mutex_destroy(&prog->mt_forks[i]);
			i++;
		}
		free(prog->mt_forks);
		prog->mt_forks = NULL;
	}
	pthread_mutex_destroy(&prog->mt_lock_print);
	pthread_mutex_destroy(&prog->mt_lock_meal);
	return (1);
}

static int	ft_philos_clean(t_program *prog)
{
	int	i;

	i = 0;
	if (prog->philos)
	{
		while (i < prog->philo_count)
		{
			if (!prog->philos[i])
				break ;
			free(prog->philos[i]);
			prog->philos[i] = NULL;
			i++;
		}
		free(prog->philos);
		prog->philos = NULL;
	}
	return (1);
}

int	ft_free(t_program *prog)
{
	ft_mutexes_clean(prog);
	ft_philos_clean(prog);
	free(prog->activated);
	return (1);
}
