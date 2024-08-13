/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:37:59 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/13 09:55:29 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/** 
 * Function to check for philosopher's death
 * 
 * Description:
 * - If a philosopher dies, it will hang the semaphore
 * so that no other philosopher could print. 
 * - The release happens in the end_process() function 
 * after signaling the sem_end to the wait_process()
 */
int	check_dead(t_philo *philo)
{
	size_t	time;

	if (sem_wait(philo->prog->sem_shared) != 0)
		return (0);
	else
	{
		time = get_current_time();
		if (philo->meal_eaten == philo->prog->must_eat + 1)
		{
			sem_post(philo->prog->sem_end);
		}
		if (time - philo->last_meal_ms >= philo->prog->time_die)
		{
			philo_msg(philo, "died");
			end_process(philo);
			sem_post(philo->prog->sem_shared);
			return (1);
		}
		else
		{
			sem_post(philo->prog->sem_shared);
			return (0);
		}
		
	}
}

void	monitor_routine(t_philo *philo)
{
	while (1)
	{
		if (check_dead(philo))
		{
			break ;
		}
	}
}

/**
 * Routine of a philosopher
 * 
 * @return exit_code [0, 1]
 */
void	*philo_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo*)v_philo;
	if (philo->id % 2 != 0)
		ft_usleep(10);
	while (1)
	{
		sem_wait(philo->prog->sem_activate);
		if (philo->prog->philo_count == 1)
			continue ;
		if (ft_pick_forks(philo))
		{
			sem_post(philo->prog->sem_activate);
			if (!ft_eat(philo))
				end_process(philo);
			if (!ft_sleep_think(philo))
				end_process(philo);
		}
		else
		{
			sem_post(philo->prog->sem_activate);
			end_process(philo);
			return (NULL);
		}
	}
	return (NULL);
}
