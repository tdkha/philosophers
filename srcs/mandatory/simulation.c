/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:57:24 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/01 22:58:27 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	simulation(t_program *prog)
{
	int	i;

	i = 0;
	if (!ft_thread(&prog->pth_monitor, monitor, (void *) prog, CREATE))
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