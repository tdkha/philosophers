/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:22:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/11 17:22:01 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_pick_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork) != 0)
	{
		error_msg("ft_pick_forks: pthread_mutex_lock\n");
		exit(1);
	}
	philo_msg(philo, "has taken a fork");
	if (philo->philo_count == 1)
		return (pthread_mutex_unlock(philo->left_fork), 0);
	if (pthread_mutex_lock(philo->right_fork) != 0)
	{
		error_msg("ft_pick_forks: pthread_mutex_lock\n");
		exit(1);
	}
	philo_msg(philo, "has taken a fork");
	return (1);
}

static void	ft_drop_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->left_fork) != 0)
		error_msg_exit("ft_drop_forks: pthread_mutex_unlock\n", 1);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		error_msg_exit("ft_drop_forks: pthread_mutex_unlock\n", 1);
}

static int	ft_eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->mt_lock) != 0)
		error_msg_exit("ft_eat: pthread_mutex_lock\n", 1);
	philo->meal_eaten++;
	philo->last_meal_ms = get_current_time();
	if (pthread_mutex_unlock(philo->mt_lock) != 0)
		error_msg_exit("ft_eat: pthread_mutex_unlock\n", 1);
	philo_msg(philo, "is eating");
	ft_usleep(philo->time_eat, philo);
	if (pthread_mutex_lock(philo->mt_lock) != 0)
		error_msg_exit("ft_eat: pthread_mutex_lock\n", 1);
	if (philo->meal_eaten == philo->must_eat)
	{
		++(*philo->philo_full_count);
	}
	if (pthread_mutex_unlock(philo->mt_lock) != 0)
		error_msg_exit("ft_eat: pthread_mutex_lock\n", 1);
	ft_drop_forks(philo);
	return (1);
}

static int	ft_sleep_think(t_philo *philo)
{
	if (!philo_msg(philo, "is sleeping"))
		return (0);
	ft_usleep(philo->time_sleep, philo);
	if (!philo_msg(philo, "is thinking"))
		return (0);
	return (1);
}

void	*philo_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	ft_usleep(philo->start_ms - get_current_time(), NULL);
	if (philo->id % 2 != 0)
		ft_usleep(philo->time_eat / 2, NULL);
	while (1)
	{
		if (ft_pick_forks(philo) == 0)
			break ;
		if (ft_eat(philo) == 0)
			break ;
		if (ft_sleep_think(philo) == 0)
			break ;
		if (check_dead(philo))
			break ;
	}
	return (NULL);
}
