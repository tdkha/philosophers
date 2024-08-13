/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:26:19 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/13 09:52:53 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	end_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->prog->philo_count)
	{
		if (sem_post(philo->prog->sem_end) != 0)
		{
			error_msg("Error: end_process from sem_post()\n");
			exit(1);
		}
		i--;
	}
}

/**
 * Function to init the processes using fork() fucntion
 */
int	create_process(t_program *prog)
{
	int			i;
	int			code;
	t_thread	thread;

	i = 0;
	code = 0;
	while (i < prog->philo_count)
	{
		prog->philos[i]->pid = fork();
		if (prog->philos[i]->pid == -1)
			return (0);
		else if (prog->philos[i]->pid == 0)
		{
			if (pthread_create(
					&thread, NULL,
					philo_routine, (void *) prog->philos[i]))
				return (0);
			monitor_routine(prog->philos[i]);
			pthread_join(thread, NULL);
			exit(code);
		}
		++i;
	}
	return (1);
}

void	wait_process(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->philo_count)
	{
		sem_wait(prog->sem_end);
		++i;
	}
	i = 0;
	while (i < prog->philo_count)
	{
		kill(prog->philos[i]->pid, SIGKILL);
		++i;
	}
	i = 0;
	while (i < prog->philo_count)
	{
		waitpid(prog->philos[i]->pid, NULL, 0);
		++i;
	}
}
