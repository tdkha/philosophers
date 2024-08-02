/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:22:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/02 13:57:56 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->mt_lock_dead);
	if (philo->died)
	{
		pthread_mutex_unlock(&philo->mt_lock_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->mt_lock_dead);
	return (0);
}

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->philo_count == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		ft_sleep(philo->time_die);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	philo_msg(philo, EAT);
}

static void	ft_sleep(t_philo *philo)
{
	philo_msg(philo, SLEEP);
	ft_usleep(philo->time_sleep, philo->mt_lock_print);
}

static void	ft_think(t_philo *philo)
{
	philo_msg(philo, THINK);
}

void	*philo_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->mt_lock_print);
	while (!check_dead(philo))
	{
		ft_philo(philo, EAT, philo->id);
		ft_philo(philo, SLEEP, philo->id);
		ft_philo(philo, THINK, philo->id);
	}
	return (NULL);
}
