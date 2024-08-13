/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:57:24 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/13 17:15:38 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_create_threads(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->philo_count)
	{
		if (pthread_create(
				&prog->philos[i]->pth, NULL,
				philo_routine, (void *)prog->philos[i]) != 0)
		{
			return (
				error_msg_ret(
					"Failed to CREATE monitor thread\n",
					&prog->mt_lock, 0));
		}
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
		{
			return (
				error_msg_ret(
					"Failed to JOIN philo thread\n",
					&prog->mt_lock, 0));
		}
		++i;
	}
	return (1);
}

static int	ft_monitor_cond(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->philo_count)
	{
		pthread_mutex_lock(&prog->mt_lock);
		if (get_current_time() - prog->philos[i]->last_meal_ms >= prog->time_die
			|| prog->philo_full_count >= prog->philo_count
		)
		{
			pthread_mutex_lock(&prog->mt_terminate);
			prog->terminate = 1;
			pthread_mutex_unlock(&prog->mt_terminate);
			print_end(prog, prog->philos[i]);
			pthread_mutex_unlock(&prog->mt_lock);
			return (1);
		}
		++i;
		pthread_mutex_unlock(&prog->mt_lock);
	}
	return (0);
}

static void	ft_monitor(t_program *prog)
{
	while (1)
	{
		if (ft_monitor_cond(prog))
			break ;
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
