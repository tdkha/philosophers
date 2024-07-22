/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:23:47 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/22 19:00:38 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_free(t_program *prog)
{
	int		i;

	i = -1;
	if (prog->mt_forks)
	{
		while (++i < prog->philo_count)
			ft_mutex(&prog->mt_forks[i], DESTROY);
		free(prog->mt_forks);
		prog->mt_forks = NULL;
	}
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
