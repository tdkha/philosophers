/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:17:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/24 10:39:58 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	check_dead(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->philo_count)
	{
		ft_mutex(&prog->mt_lock_dead, LOCK, prog);
		
		ft_mutex(&prog->mt_lock_dead, UNLOCK, prog);
		++i;
	}
}

static void	check_full(t_program *prog)
{
	
}

void	*monitor_routine(void *v_prog)
{
	t_program	*prog;

	prog = (t_program *) v_prog;
	while (1)
	{
		
	}
	return (v_prog);
}
