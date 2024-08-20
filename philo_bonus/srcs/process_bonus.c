/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:26:19 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/20 08:20:35 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	end_process_clean(t_philo *philo)
{
	t_program	*prog;
	int			i;

	prog = philo->prog;
	i = 0;
	if (prog->philos)
	{
		while (i < prog->philo_count)
		{
			if (!prog->philos[i])
				break ;
			sem_close(prog->sem_forks);
			sem_close(prog->sem_shared);
			sem_close(prog->sem_activate);
			sem_close(prog->sem_print);
			sem_close(prog->sem_terminate);
			free(prog->philos[i]);
			prog->philos[i] = NULL;
			i++;
		}
		free(prog->philos);
		prog->philos = NULL;
	}
	free(prog);
}

int	end_process_exit(char *str, int exit_code)
{
	error_msg(str);
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
			pthread_create(&thread, NULL,
				philo_routine, (void *) prog->philos[i]);
			exit_code = monitor_routine(prog->philos[i]);
			pthread_join(thread, NULL);
			end_process_clean(prog->philos[i]);
			exit(exit_code);
		}
		++i;
	}
	return (1);
}

void	waiter_exitcode_handler(
	t_program *prog,
	int *status,
	int *count_full)
{
	int	exit_code;

	if (WIFEXITED(*status))
	{
		exit_code = WEXITSTATUS(*status);
		if (exit_code == 1)
			error_msg("waiter_exitcode_handler: system error\n");
		else if (exit_code == PHILO_FULL)
			++(*count_full);
		if (exit_code == 1 || exit_code == PHILO_DEAD)
		{
			ft_kill_processes(prog);
		}
	}
}

void	wait_process(t_program *prog)
{
	int	i;
	int	status;
	int	count_full;

	i = 0;
	status = 0;
	count_full = 0;
	while (i < prog->philo_count)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			error_msg("wait_process: waitpid \n");
			ft_kill_processes(prog);
		}
		waiter_exitcode_handler(prog, &status, &count_full);
		++i;
	}
	if (count_full == prog->must_eat)
		printf("All philosophers have eaten %d meals\n", count_full);
}
