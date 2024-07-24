/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:22:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/23 20:52:10 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"



static void	*monitor_routine(void *v_prog)
{
	t_program	*prog;

	prog = (t_program *) v_prog;
}

static void	*philo_routine(void *v_philo)
{
	
}

static int	start_phase(t_program *prog)
{
	int	i;

	i = 0;
	//----------------------------------
	// <1> Start the monitor thread
	//----------------------------------
	if (!ft_thread(&prog->pth_monitor, monitor_routine, (void *) prog, CREATE))
		return (0);
	while (i < prog->philo_count)
	{
		if (ft_thread(&prog->philos[i]->pth, philo_routine, (void *)prog, CREATE))
		{
			// failed to create thread representing <t_philo *>
			return (0);
		}
		++i;
	}
	return (1);
}

static int	end_phase(t_program *prog)
{
	int	i;

	i = 0;
	
	return (i);
}

int	philosopher(t_program *prog)
{
	int	success;
	
	success = start_phase(prog);
	if (success)
		success = end_phase(prog);
	return (success);
}