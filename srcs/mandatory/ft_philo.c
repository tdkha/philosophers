/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:06:33 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/31 12:48:56 by ktieu            ###   ########.fr       */
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
	else if (status == FORK_DOWN_R && nth_fork >= 0)
		ft_mutex(&philo->prog->mt_forks[nth_fork], UNLOCK, philo->prog);
	
	philo_msg(philo, status);
}

static inline void ft_eat(
	t_philo *philo,
	t_program *prog,
	int nth_fork
)
{
	ft_put_fork(philo, FORK_UP_L, nth_fork);
	if (prog->philo_count == 1)
	{
		ft_put_fork(philo, FORK_DOWN_L, nth_fork);
		ft_usleep(prog->time_die, prog);
		return ;
	}
	ft_put_fork(philo, FORK_UP_R, nth_fork);
	
	philo->eating = 1;
	philo_msg(philo, EAT);
	
	ft_mutex(&prog->mt_lock_meal, LOCK, prog);
	philo->last_meal_ms = get_current_time(prog);
	philo->meal_eaten++;
	ft_mutex(&prog->mt_lock_meal, UNLOCK, prog);
	
	ft_usleep(prog->time_eat, prog);
	philo->eating = 0;
	ft_put_fork(philo, FORK_DOWN_L, nth_fork);
	ft_put_fork(philo, FORK_DOWN_R, nth_fork);
}

void ft_philo(
	t_philo *philo,
	t_program *prog,
	t_philo_status status,
	int nth_fork)
{
	if (status == EAT && nth_fork >= 0)
	{
		ft_eat(philo, prog, nth_fork);
	}
	else if (status == SLEEP)
	{
		philo_msg(philo, SLEEP);
		ft_usleep(philo->prog->time_sleep, philo->prog);
	}
	else if (status  == THINK)
		philo_msg(philo, THINK);
}
