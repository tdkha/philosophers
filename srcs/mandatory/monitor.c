/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:17:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/29 00:58:40 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	check_dead(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->philo_count)
	{
		ft_mutex(&prog->mt_lock_dead, LOCK, prog);
		if (get_current_time(prog) - prog->philos[i]->last_meal_ms >= prog->time_die)
		{
			prog->terminate = 1;
			prog->philos[i]->status = DIE;
			ft_mutex(&prog->mt_lock_dead, UNLOCK, prog);
			return (1);
		}
		++i;
		ft_mutex(&prog->mt_lock_dead, UNLOCK, prog);
	}
	return (0);
}

static void	check_full(t_program *prog)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	while (i < prog->philo_count)
	{
		ft_mutex(&prog->mt_lock_dead, LOCK, prog);
		if (prog->philos[i]->meal_eaten >= prog->must_eat)
			finished++;
		++i;
		ft_mutex(&prog->mt_lock_dead, UNLOCK, prog);
	}
	if (finished == prog->philo_count)
	{
		ft_mutex(&prog->mt_lock_dead, LOCK, prog);
		prog->terminate = 1;
		ft_mutex(&prog->mt_lock_dead, UNLOCK, prog);
	}
}

static int	is_empty(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->philo_count)
	{
		if (prog->activated[i] != 0)
			return (0);
		++i;
	}
	return (1);
}

static void	check_activate(t_program *prog)
{
	int	i;
	
	i = -1;
	if (!prog->terminate && is_empty(prog))
	{
		while (++i < prog->philo_count)
		{
			if (i % 2 == prog->odd_flag)
				prog->activated[i] = 1;
		}
		if (prog->odd_flag == 0)
			prog->odd_flag = 1;
		else
			prog->odd_flag = 0;
	}
}

void	*monitor_routine(void *v_prog)
{
	t_program	*prog;

	prog = (t_program *) v_prog;
	while (!check_dead(prog))
	{
		check_full(prog);
		check_activate(prog);
	}
	printf("Philo died, program terminated\n");
	return (v_prog);
}
