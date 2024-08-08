/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:26:19 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/08 14:44:34 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	end_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->prog->philo_count)
	{
		if (sem_post(philo->prog->sem_end) != 0)
		{
			error_msg("Error in end_process from sem_post()\n", philo->prog->sem_shared);
			exit(1);
		}
		i--;;
	}
}

/**
 * Function to init the processes using fork() fucntion
 */
int	create_process(t_program *prog)
{
	int			i;
	int			code;
	t_thread	monitor_thrd;

	i = 0;
	code = 0;
	while (i < prog->philo_count)
	{
		prog->philos[i]->pid = fork();
		if (prog->philos[i]->pid == -1)
			return (0);
		else if (prog->philos[i]->pid == 0)
		{
			if (pthread_create(&monitor_thrd, NULL, monitor_routine, (void *) prog->philos[i]))
				return (0);
			if (pthread_detach(monitor_thrd))
				return (0);
			code = philo_routine(prog->philos[i]);
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
	i = 1;
	while (i < prog->philo_count)
	{
		kill(prog->philos[i]->pid, SIGKILL);	
		++i;
	}
	kill(prog->philos[0]->pid, SIGKILL); 
}