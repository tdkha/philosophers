/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:26:19 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/15 16:39:57 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	end_process_clean(t_philo *philo)
{
	t_program	*prog;

	prog = philo->prog;
	sem_unlink(philo->sem_name);
	sem_close(philo->sem_terminate);
	ft_philos_clean(prog);
	free(prog);
}

int	end_process_exit(t_philo *philo, int exit_code)
{
	t_program	*prog;

	prog = philo->prog;
	sem_unlink(philo->sem_name);
	sem_close(philo->sem_terminate);
	ft_philos_clean(prog);
	free(prog);
	exit (exit_code);
}

/**
 * Function to init the processes using fork() fucntion
 */
int	create_process(t_program *prog)
{
	int			i;
	int			exit_code;
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
			exit_code = monitor_routine(prog->philos[i]);
			pthread_join(thread, NULL);
			end_process_clean(prog->philos[i]);
			printf("EXIT CODE: %d\n", exit_code);
			return (exit_code);
		}
		++i;
	}
	return (1);
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

void	wait_process(t_program *prog)
{
	int	i;
	int	status;

	i = 0;
	while (i < prog->philo_count)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			error_msg("philo_bonus: wait_process: waitpid\n");
			ft_kill_processes(prog);
		}
		if (status == 1)
		{
			error_msg("philo_bonus: exit code is 1\n");
			ft_kill_processes(prog);
		}
		else if (status == PHILO_FULL)
		{
			printf("All philosophers have eaten %d meals\n", prog->must_eat);
		}
		else if (status == PHILO_DEAD)
		{
			printf("All philosophers have eaten %d meals\n", prog->must_eat);
			ft_kill_processes(prog);
		}
		++i;
	}
}
