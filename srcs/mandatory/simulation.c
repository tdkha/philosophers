/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:57:24 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/03 16:29:37 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	ft_create_threads(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->philo_count)
	{
		if (pthread_create(&prog->philos[i]->pth, NULL, philo_routine, (void *)prog->philos[i]) != 0)
			return (error_msg_ret("Failed to CREATE monitor thread\n", &prog->mt_lock_print, 0));
		++i;
	}
	return (1);
}

static int	ft_join_threads(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->philo_count)
	{
		if (pthread_join(prog->philos[i]->pth, NULL) != 0)
			return (error_msg_ret("Failed to JOIN philo thread\n", &prog->mt_lock_print, 0));
		++i;
	}
	return (1);
}

static void	ft_monitor(t_program *prog)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < prog->philo_count)
		{
			pthread_mutex_lock(&prog->mt_lock);
			if (get_current_time(&prog->mt_lock_print) - prog->philos[i]->last_meal_ms >= prog->time_die
				|| prog->philos[i]->meal_eaten == prog->must_eat
			)
			{
				prog->terminate = 1;
				if (prog->must_eat != -1 && prog->philos[i]->meal_eaten == prog->must_eat)
					printf("Every philosopher ate %d times\n", prog->must_eat);
				else
					printf("%zu %d died\n"
						, get_current_time(&prog->mt_lock_print) - prog->philos[i]->start_ms, i + 1);
				pthread_mutex_unlock(&prog->mt_lock);
				break ;
			}
			++i;
			pthread_mutex_unlock(&prog->mt_lock);
		}
	}
}

int	simulation(t_program *prog)
{
	if (!ft_create_threads(prog))
		return (0);
	ft_monitor(prog);
	if (!ft_join_threads(prog))
		return (0);
	return (1);
}
