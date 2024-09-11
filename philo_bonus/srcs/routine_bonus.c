/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:37:59 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/11 17:37:39 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	ft_one_philo_routine(t_philo *philo)
{
	if (sem_wait(philo->prog->sem_forks) != 0)
	{
		error_msg("ft_one_philo_routine: sem_wait\n");
		exit(1);
	}
	philo_msg(philo, "has taken a fork");
	if (sem_post(philo->prog->sem_forks) != 0)
	{
		error_msg("ft_one_philo_routine: sem_post\n");
		exit(1);
	}
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
	ft_usleep(philo->start_ms - get_current_time(), NULL);
	if (philo->id % 2 != 0)
		ft_usleep(philo->prog->time_eat / 2, NULL);
	while (1)
	{
		if (ft_check_terminate(philo))
			break ;
		if (philo->prog->philo_count == 1)
		{
			ft_one_philo_routine(philo);
			break ;
		}
		ft_eat(philo);
		ft_sleep_think(philo);
	}
	return (NULL);
}
