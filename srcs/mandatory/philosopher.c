/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:22:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/03 16:28:49 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"


static int	ft_pick_forks(t_philo *philo)
{
	if (check_dead(philo))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	if (philo_msg(philo, FORK_UP_L) == 0)
		return (pthread_mutex_unlock(philo->left_fork), 0);
	if (check_dead(philo) || philo->philo_count == 1)
		return (pthread_mutex_unlock(philo->left_fork), 0);
	pthread_mutex_lock(philo->right_fork);
	if (philo_msg(philo, FORK_UP_R) == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	return (1);
}

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mt_lock);
	philo->meal_eaten++;
	philo->last_meal_ms = get_current_time(philo->mt_lock_print);
	pthread_mutex_unlock(philo->mt_lock);
	philo_msg(philo, EAT);
	ft_usleep(philo->time_sleep, philo->mt_lock_print);
	pthread_mutex_lock(philo->mt_lock);
	if (philo->meal_eaten == philo->must_eat)
	{
		(*philo->philo_full_count)++;
	}
	pthread_mutex_unlock(philo->mt_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	ft_sleep_think(t_philo *philo)
{
	if (!philo_msg(philo, SLEEP))
		return(0);
	ft_usleep(philo->time_sleep, philo->mt_lock_print);
	if (!philo_msg(philo, THINK))
	{
		return(0);
	}
	return (1);
}

void	*philo_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->mt_lock_print);
	while (1)
	{
		if (ft_pick_forks(philo) == 0)
			break ;
		ft_eat(philo);
		if (ft_sleep_think(philo) == 0)
			break ;
	}
	return (NULL);
}
