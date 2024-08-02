/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:22:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/01 23:08:40 by ktieu            ###   ########.fr       */
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

static void	*philosophers(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->prog);
	while (!check_dead(philo))
	{
		ft_philo(philo, EAT, philo->id);
		ft_philo(philo, SLEEP, philo->id);
		ft_philo(philo, THINK, philo->id);
	}
	return (NULL);
}
