/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:26:19 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/15 10:49:10 by ktieu            ###   ########.fr       */
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
			error_msg("philo_bonus: end_process: sem_post()\n");
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
	t_thread	thread;

	i = 0;
	while (i < prog->philo_count)
	{
		prog->philos[i]->pid = fork();
		if (prog->philos[i]->pid == -1)
			return (0);
		else if (prog->philos[i]->pid == 0)
		{
			pthread_create(&thread, NULL, philo_routine, (void *) prog->philos[i]);
			monitor_routine(prog->philos[i]);
			pthread_join(thread, NULL);
			sem_destroy(&prog->philos[i]->sem_terminate);
			return (0);
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

void	wait_process_beta(t_program *prog)
{
	int	i;
	int	status;

	i = 0;
	while (i < prog->philo_count)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			error_msg("philo_bonus: wait_process: waitpid\n");
		}

		++i;
	}
}
