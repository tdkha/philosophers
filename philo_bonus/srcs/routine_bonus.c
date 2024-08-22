/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:37:59 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/22 17:45:20 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	repeated_cycle(t_philo *philo)
{
	if (ft_pick_forks(philo))
	{
		ft_eat(philo);
		ft_sleep_think(philo);
	}
	else
		return (0);
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
	philo->start_ms += 3000;
	philo->last_meal_ms = philo->start_ms;
	ft_usleep(philo->start_ms - get_current_time());
	if (philo->id % 2 != 0)
		ft_usleep(10);
	while (1)
	{
		if (ft_check_terminate(philo))
			break ;
		if (philo->prog->philo_count == 1)
			continue ;
		if (repeated_cycle(philo) == 0)
			end_process_exit("repeated_cycle: sem errors\n", 1);
	}
	return (NULL);
}
