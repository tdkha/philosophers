/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:37:59 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/15 16:38:41 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/** 
 * Function to check for philosopher's death
 * 
 */
static int	check_dead(t_philo *philo)
{
	size_t	time;

	if (sem_wait(philo->prog->sem_shared) != 0)
		end_process_exit(philo, 1);
	else
	{
		time = get_current_time();
		if (time - philo->last_meal_ms >= philo->prog->time_die)
		{
			philo_msg(philo, "died");
			sem_wait(philo->sem_terminate);
			philo->terminate = 1;
			sem_post(philo->sem_terminate);
			sem_post(philo->prog->sem_shared);
			return (1);
		}
		else
		{
			sem_post(philo->prog->sem_shared);
			return (0);
		}
	}
	return (0);
}

static int	check_full(t_philo *philo)
{
	if (sem_wait(philo->prog->sem_shared) != 0)
		end_process_exit(philo , 1);
	else
	{
		if (philo->meal_eaten == philo->prog->must_eat)
		{
			sem_wait(philo->sem_terminate);
			philo->terminate = 1;
			sem_post(philo->sem_terminate);
			sem_post(philo->prog->sem_shared);
			return (1);
		}
		else
		{
			sem_post(philo->prog->sem_shared);
			return (0);
		}
	}
	return (0);
}


int	monitor_routine(t_philo *philo)
{
	while (1)
	{
		if (check_dead(philo))
			return (PHILO_DEAD);
		if (check_full(philo))
			return (PHILO_FULL);
	}
	return (0);
}

static int	repeated_cycle(t_philo *philo)
{
	if (ft_pick_forks(philo))
	{
		if (sem_post(philo->prog->sem_activate) != 0)
		{
			return (0);
		}
		if (!ft_eat(philo))
			return (0);
		if (!ft_sleep_think(philo))
			return (0);
	}
	else
	{
		sem_post(philo->prog->sem_activate);
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
		ft_usleep(10);
	while (1)
	{
		if (ft_check_terminate(philo))
			break ;
		if (sem_wait(philo->prog->sem_activate) != 0)
			end_process_exit(philo , 1);
		if (philo->prog->philo_count == 1)
		{
			sem_post(philo->prog->sem_activate);
			continue ;
		}
		if (repeated_cycle(philo) == 0)
			end_process_exit(philo , 1);
	}
	return (NULL);
}
