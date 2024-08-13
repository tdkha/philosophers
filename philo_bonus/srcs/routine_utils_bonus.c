/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:59:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/13 09:50:47 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_pick_forks(t_philo *philo)
{
	if (sem_wait(philo->prog->sem_forks) != 0)
		return (0);
	philo_msg(philo, "has taken a fork");
	if (sem_wait(philo->prog->sem_forks) != 0)
		return (0);
	philo_msg(philo, "has taken a fork");
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
	sem_wait(philo->prog->sem_shared);
	philo->meal_eaten++;
	philo->last_meal_ms = get_current_time();
	sem_post(philo->prog->sem_shared);
	if (philo_msg(philo, "is eating") == 0)
	{
		ft_drop_forks(philo); // Ensure forks are dropped in case of error
		return (0);
	}
	ft_usleep(philo->prog->time_eat);
	sem_wait(philo->prog->sem_shared);
	sem_post(philo->prog->sem_shared);
	if (!ft_drop_forks(philo))
		return (0);
	return (1);
}


int	ft_sleep_think(t_philo *philo)
{
	if (philo_msg(philo, "is sleeping") == 0)
		return (0);
	ft_usleep(philo->prog->time_sleep);
	if (philo_msg(philo, "is thinking") == 0)
		return (0);
	return (1);
}
