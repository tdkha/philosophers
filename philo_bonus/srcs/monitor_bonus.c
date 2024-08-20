/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:47:02 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/20 08:46:07 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	ft_philo_terminate(t_philo *philo)
{
	if (sem_wait(philo->prog->sem_terminate) != 0)
		end_process_exit("ft_philo_terminate: sem_wait\n", 1);
	philo->terminate = 1;
	if (sem_post(philo->prog->sem_terminate) != 0)
		end_process_exit("ft_philo_terminate: sem_post\n", 1);
}

/** 
 * Function to check for philosopher's death
 * 
 */
static int	check_dead(t_philo *philo)
{
	size_t	time;

	if (sem_wait(philo->prog->sem_shared) != 0)
		end_process_exit("check_dead: sem_wait\n", 1);
	else
	{
		time = get_current_time();
		if (time - philo->last_meal_ms >= philo->prog->time_die)
		{
			ft_philo_terminate(philo);
			if (sem_wait(philo->prog->sem_print) != 0)
				end_process_exit("check_dead: sem_wait\n", 1);
			printf("%zu %d died\n", time - philo->start_ms, philo->id + 1);
			if (sem_post(philo->prog->sem_shared) != 0)
				end_process_exit("check_dead: sem_post\n", 1);
			return (1);
		}
		else
		{
			if (sem_post(philo->prog->sem_shared) != 0)
				end_process_exit("check_dead: sem_post\n", 1);
			return (0);
		}
	}
	return (0);
}

static int	check_full(t_philo *philo)
{
	if (sem_wait(philo->prog->sem_shared) != 0)
		end_process_exit("check_full: sem_wait\n", 1);
	else
	{
		if (philo->meal_eaten == philo->prog->must_eat)
		{
			ft_philo_terminate(philo);
			if (sem_post(philo->prog->sem_shared) != 0)
				end_process_exit("check_full: sem_post\n", 1);
			return (1);
		}
		else
		{
			if (sem_post(philo->prog->sem_shared) != 0)
				end_process_exit("check_full: sem_post\n", 1);
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
