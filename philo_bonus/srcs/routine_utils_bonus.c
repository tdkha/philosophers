/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:59:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/05 11:13:21 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_check_terminate(t_philo *philo)
{
	if (sem_wait(philo->sem_terminate) != 0)
	{
		error_msg("ft_check_terminate: sem_wait\n");
		exit(1);
	}
	if (philo->terminate)
	{
		sem_post(philo->sem_terminate);
		return (1);
	}
	if (sem_post(philo->sem_terminate) != 0)
	{
		error_msg("ft_check_terminate: sem_post\n");
		exit(1);
	}
	return (0);
}

/**
 * Function to pick forks
 * 
 * Note: Do not exit if semaphore fails. Handle from the calling function
 */
int	ft_pick_forks(t_philo *philo)
{
	if (sem_wait(philo->prog->sem_forks) != 0)
	{
		error_msg("ft_pick_forks: sem_wait\n");
		exit(1);
	}
	philo_msg(philo, "has taken a fork");
	if (sem_wait(philo->prog->sem_forks) != 0)
	{
		error_msg("ft_pick_forks: sem_wait\n");
		exit(1);
	}
	philo_msg(philo, "has taken a fork");
	return (1);
}

/**
 * Function to drop forks
 * 
 * Note: Do not exit if semaphore fails. Handle from the calling function
 */
int	ft_drop_forks(t_philo *philo)
{
	if (sem_post(philo->prog->sem_forks) != 0)
	{
		error_msg("ft_drop_forks: sem_post\n");
		exit(1);
	}
	if (sem_post(philo->prog->sem_forks) != 0)
	{
		error_msg("ft_drop_forks: sem_post\n");
		exit(1);
	}
	return (1);
}

int	ft_eat(t_philo *philo)
{
	ft_pick_forks(philo);
	if (sem_wait(philo->sem_shared) != 0)
	{
		error_msg("ft_eat: sem_wait\n");
		exit(1);
	}
	philo->last_meal_ms = get_current_time();
	philo->meal_eaten++;
	philo_msg(philo, "is eating");
	if (sem_post(philo->sem_shared) != 0)
	{
		error_msg("ft_eat: sem_post\n");
		exit(1);
	}
	ft_usleep(philo->prog->time_eat);
	ft_drop_forks(philo);
	return (1);
}

int	ft_sleep_think(t_philo *philo)
{
	philo_msg(philo, "is sleeping");
	ft_usleep(philo->prog->time_sleep);
	philo_msg(philo, "is thinking");
	usleep(1000);
	return (1);
}
