/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:59:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/19 18:06:04 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_check_terminate(t_philo *philo)
{
	sem_wait(philo->prog->sem_terminate);
	if (philo->terminate)
	{
		sem_post(philo->prog->sem_terminate);
		return (1);
	}
	sem_post(philo->prog->sem_terminate);
	return (0);
}

int	ft_pick_forks(t_philo *philo)
{
	if (sem_wait(philo->prog->sem_forks) != 0)
		return (0);
	if (philo_msg(philo, "has taken a fork") == 0)
		return (0);
	if (sem_wait(philo->prog->sem_forks) != 0)
		return (0);
	if (philo_msg(philo, "has taken a fork") == 0)
		return (0);
	return (1);
}

int	ft_drop_forks(t_philo *philo)
{
	if (sem_post(philo->prog->sem_forks) != 0)
		return (0);
	if (sem_post(philo->prog->sem_forks) != 0)
		return (0);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	philo_msg(philo, "is eating");
	sem_wait(philo->prog->sem_shared);
	philo->last_meal_ms = get_current_time();
	philo->meal_eaten++;
	sem_post(philo->prog->sem_shared);
	ft_usleep(philo->prog->time_eat);
	if (!ft_drop_forks(philo))
		return (0);
	return (1);
}

int	ft_sleep_think(t_philo *philo)
{
	philo_msg(philo, "is sleeping");
	ft_usleep(philo->prog->time_sleep);
	philo_msg(philo, "is thinking");
	ft_usleep(philo->prog->time_think);
	return (1);
}
