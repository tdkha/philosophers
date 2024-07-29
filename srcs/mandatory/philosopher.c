/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:22:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/29 01:32:51 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * Function to put a single fork. The order of picking fork of the last philo willl be different.
 * 
 * Explantation:
 * 
 * - Philo 0:
 * 	ft_min(0, 1) -> 0 (pick left fork)
 * 	ft_max(0, 1 % 5) -> 1 (pick right fork)
 * 
 * - Philo 5 (max):
 * 	ft_min(4, (4 + 1) % 5) -> 0 (pick right fork)
 * 	ft_max(4, (4 + 1) % 5) -> 4 (pick left fork)
 */
static void	ft_put_fork(
	t_philo *philo,
	t_philo_status status,
	int nth_fork
)
{
	if (status == FORK_UP_L || status == FORK_DOWN_L)
		nth_fork = ft_min(nth_fork, (nth_fork + 1) % philo->prog->philo_count);
	else if (status == FORK_UP_R || status == FORK_DOWN_R)
		nth_fork = ft_max(nth_fork, (nth_fork + 1) % philo->prog->philo_count);
	if (status == FORK_UP_L && nth_fork >= 0)
		ft_mutex(&philo->prog->mt_forks[nth_fork], LOCK, philo->prog);
	else if (status == FORK_UP_R && nth_fork >= 0)
		ft_mutex(&philo->prog->mt_forks[nth_fork], LOCK, philo->prog);
	else if (status == FORK_DOWN_L && nth_fork >= 0)
		ft_mutex(&philo->prog->mt_forks[nth_fork], UNLOCK, philo->prog);
	else if (status == FORK_DOWN_L && nth_fork >= 0)
		ft_mutex(&philo->prog->mt_forks[nth_fork], UNLOCK, philo->prog);
}

static void ft_philo(
	t_philo *philo,
	t_philo_status status,
	int nth_fork)
{
	if (status == EAT && nth_fork >= 0)
	{
		ft_put_fork(philo, FORK_UP_L, nth_fork);
		ft_put_fork(philo, FORK_UP_R, nth_fork);
		philo_msg(philo, EAT);
		ft_put_fork(philo, FORK_DOWN_L, nth_fork);
		ft_put_fork(philo, FORK_DOWN_R, nth_fork);
	}
	else if (status == SLEEP)
	{
		philo_msg(philo, SLEEP);
		ft_usleep(philo->prog->time_sleep, philo->prog);
	}
	else if (status  == THINK)
		philo_msg(philo, THINK);
}

static void	*philo_routine(void *v_philo)
{
	t_philo	*philo;
	size_t	time;

	philo = (t_philo *)v_philo;
	philo->start_ms = get_current_time(philo->prog);
	while (1)
	{
		printf("Locking mutex from philo %d\n", philo->id);
		ft_mutex(&philo->prog->mt_lock_dead, LOCK, philo->prog);
		time = get_current_time(philo->prog) - philo->last_meal_ms;
		if (philo->prog->terminate || time >= philo->prog->time_die)
		{
			philo->status = DIE;
			philo->prog->terminate = 1;
			ft_mutex(&philo->prog->mt_lock_dead, UNLOCK, philo->prog);
			return (NULL);
		}
		ft_mutex(&philo->prog->mt_lock_dead, UNLOCK, philo->prog);

		ft_philo(philo, EAT, philo->id);
		ft_philo(philo, SLEEP, philo->id);
		ft_philo(philo, THINK, philo->id);
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
		printf("Philo id: %d\n", prog->philos[i]->id);
		if (!ft_thread(&prog->philos[i]->pth, philo_routine, (void *)prog->philos[i], CREATE))
			return (0);
		++i;
	}
	i = 0;
	while (i < prog->philo_count)
	{
		if (!ft_thread(&prog->philos[i]->pth, philo_routine, (void *)prog->philos[i], JOIN))
			return (0);
		++i;
	}
	return (1);
}