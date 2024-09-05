/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:37:59 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/05 11:13:41 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
	ft_usleep(philo->start_ms - get_current_time());
	if (philo->id % 2 != 0)
		ft_usleep(philo->prog->time_eat / 2);
	while (1)
	{
		if (ft_check_terminate(philo))
			break ;
		if (philo->prog->philo_count == 1)
			continue ;
		ft_eat(philo);
		ft_sleep_think(philo);
	}
	return (NULL);
}
