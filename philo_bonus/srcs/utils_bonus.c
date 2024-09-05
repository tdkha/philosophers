/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:17:27 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/05 13:51:45 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (philo)
		{
			if (sem_wait(philo->sem_terminate) != 0)
				end_process_exit("ft_usleep: sem_wait: sem_terminate\n", 1);
			if (philo->terminate)
			{
				if (sem_post(philo->sem_terminate) != 0)
					end_process_exit("ft_usleep: sem_post: sem_terminate\n", 1);
				return ;
			}
			if (sem_post(philo->sem_terminate) != 0)
				end_process_exit("ft_usleep: sem_post: sem_terminate\n", 1);
		}
		usleep(500);
	}
}

void	ft_kill_processes(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->philo_count)
	{
		kill(prog->philos[i]->pid, SIGKILL);
		++i;
	}
}
