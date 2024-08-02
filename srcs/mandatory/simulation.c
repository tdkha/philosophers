/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:57:24 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/02 13:38:20 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	simulation(t_program *prog)
{
	int	i;

	i = 0;
	if (pthread_create(&prog->pth_monitor, NULL, monitor_routine, (void *)prog) != 0)
		return (error_msg_ret("Failed to CREATE monitor thread\n", &prog->mt_lock_print, 0));
	while (i < prog->philo_count)
	{
		if (pthread_create(&prog->philos[i]->pth, NULL, philo_routine, (void *)prog->philos[i]) != 0)
			return (error_msg_ret("Failed to CREATE monitor thread\n", &prog->mt_lock_print, 0));
		++i;
	}
	if (pthread_join(prog->pth_monitor, NULL) != 0)
		return (error_msg_ret("Failed to JOIN monitor thread\n", &prog->mt_lock_print, 0));
	i = 0;
	while (i < prog->philo_count)
	{
		if (pthread_join(prog->philos[i]->pth, NULL) != 0)
			return (error_msg_ret("Failed to JOIN philo thread\n", &prog->mt_lock_print, 0));
		++i;
	}
	return (1);
}
