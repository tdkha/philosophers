/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:22:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/13 10:11:23 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_pick_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo_msg(philo, "has taken a fork") == 0)
		return (pthread_mutex_unlock(philo->left_fork), 0);
	if (philo->philo_count == 1)
		return (pthread_mutex_unlock(philo->left_fork), 0);
	pthread_mutex_lock(philo->right_fork);
	if (philo_msg(philo, "has taken a fork") == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	return (1);
}

static int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mt_lock);
	philo->meal_eaten++;
	philo->last_meal_ms = get_current_time();
	pthread_mutex_unlock(philo->mt_lock);
	if (philo_msg(philo, "is eating") == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	ft_usleep(philo->time_eat);
	pthread_mutex_lock(philo->mt_lock);
	if (philo->meal_eaten == philo->must_eat)
	{
		++(*philo->philo_full_count);
	}
	pthread_mutex_unlock(philo->mt_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

static int	ft_sleep_think(t_philo *philo)
{
	if (!philo_msg(philo, "is sleeping"))
		return (0);
	ft_usleep(philo->time_sleep);
	if (!philo_msg(philo, "is thinking"))
		return (0);
	return (1);
}

void	*philo_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	if (philo->id % 2 != 0)
		ft_usleep(10);
	while (1)
	{
		if (ft_pick_forks(philo) == 0)
			break ;
		if (ft_eat(philo) == 0)
		{
			break ;
		}
		if (ft_sleep_think(philo) == 0)
		{
			break ;
		}
	}
	return (NULL);
}
