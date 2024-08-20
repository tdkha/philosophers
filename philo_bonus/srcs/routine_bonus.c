/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:37:59 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/20 08:33:01 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	repeated_cycle(t_philo *philo)
{
	if (ft_pick_forks(philo))
	{
		if (sem_post(philo->prog->sem_activate) != 0)
			end_process_exit("repeated_cycle: sem_post\n", 1);
		ft_eat(philo);
		ft_sleep_think(philo);
	}
	else
	{
		if (sem_post(philo->prog->sem_activate) != 0)
			end_process_exit("repeated_cycle: sem_post\n", 1);
		return (0);
	}
	return (1);
}

/**
 * Routine of a philosopher
 * 
 * Desciption:
 * 
 * - The routine runs in a while-true loop
 */
void	*philo_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *) v_philo;
	if (philo->id % 2 != 0)
		ft_usleep(5);
	while (1)
	{
		if (ft_check_terminate(philo))
			break ;
		if (sem_wait(philo->prog->sem_activate) != 0)
			end_process_exit("philo_routine: sem_wait\n", 1);
		if (philo->prog->philo_count == 1)
		{
			if (sem_post(philo->prog->sem_activate) != 0)
				end_process_exit("philo_routine: sem_post\n", 1);
			continue ;
		}
		if (repeated_cycle(philo) == 0)
			end_process_exit("repeated_cycle: sem errors\n", 1);
	}
	return (NULL);
}
