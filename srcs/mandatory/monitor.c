/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:17:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/30 11:25:14 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(&philo->prog->mt_lock_meal);
	if (get_current_time(philo->prog) - philo->last_meal_ms >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(&philo->prog->mt_lock_meal), 1);
	pthread_mutex_unlock(&philo->prog->mt_lock_meal);
	return (0);
}

static int	check_dead(t_program *prog)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < prog->philo_count)
	{
		philo = prog->philos[i];
		if (philosopher_dead(philo, philo->prog->time_die))
		{
			philo_msg(philo, DIE);
			pthread_mutex_lock(&prog->mt_lock_dead);
			while (i-- > 0)
			{
				prog->philos[i]->dead = 1;
			}
			pthread_mutex_unlock(&prog->mt_lock_dead);
			return (1);
		}
		++i;
	}
	return (0);
}

static int	check_full(t_program *prog)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (prog->must_eat == -1)
		return (0);
	while (i < prog->philo_count)
	{
		ft_mutex(&prog->mt_lock_dead, LOCK, prog);
		if (prog->philos[i]->meal_eaten >= prog->must_eat)
			++finished;
		ft_mutex(&prog->mt_lock_dead, UNLOCK, prog);
		++i;
	}
	if (finished == prog->philo_count)
	{
		ft_mutex(&prog->mt_lock_meal, LOCK, prog);
		prog->philos[0]->dead = 1;
		ft_mutex(&prog->mt_lock_meal, UNLOCK, prog);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *v_prog)
{
	t_program	*prog;

	prog = (t_program *) v_prog;
	while (1)
	{
		if (check_dead(prog) || check_full(prog))
			break ;
	}
	return (NULL);
}
