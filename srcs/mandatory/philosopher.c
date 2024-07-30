/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:22:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/30 11:00:59 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int check_self_dead(t_philo *philo)
{
	t_program	*prog;

	prog = philo->prog;
	ft_mutex(&prog->mt_lock_dead, LOCK, prog);
	if (philo->dead)
	{
		return (ft_mutex(&prog->mt_lock_dead, UNLOCK, prog));
	}
	ft_mutex(&prog->mt_lock_dead, UNLOCK, prog);
	return (0);
}

static void	*philo_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->prog);
	while (!check_self_dead(philo))
	{
		ft_philo(philo, philo->prog, EAT, philo->id);
		ft_philo(philo, philo->prog, SLEEP, philo->id);
		ft_philo(philo, philo->prog, THINK, philo->id);
	}
	return (NULL);
}

int	philosopher(t_program *prog)
{
	int	i;

	i = 0;
	if (!ft_thread(&prog->pth_monitor, monitor_routine, (void *) prog, CREATE))
		return (0);
	while (i < prog->philo_count)
	{
		if (!ft_thread(&prog->philos[i]->pth, philo_routine, (void *)prog->philos[i], CREATE))
			return (0);
		++i;
	}
	if (!ft_thread(&prog->pth_monitor, NULL, NULL, JOIN))
		return (0);
	i = 0;
	while (i < prog->philo_count)
	{
		if (!ft_thread(&prog->philos[i]->pth, philo_routine, (void *)prog->philos[i], JOIN))
			return (0);
		++i;
	}
	return (1);
}
