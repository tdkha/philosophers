/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:17:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/26 08:04:59 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	check_dead(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->philo_count)
	{
		++i;
	}
}

static void	check_full(t_program *prog)
{
	
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
	if (is_empty(prog))
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
	while (1)
	{
		ft_mutex(&prog->mt_lock_dead, LOCK, prog);
		check_dead(prog);
		check_activate(prog);
		ft_mutex(&prog->mt_lock_dead, UNLOCK, prog);
	}
	return (v_prog);
}
