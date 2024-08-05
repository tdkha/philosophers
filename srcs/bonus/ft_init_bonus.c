/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:16:37 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/05 14:50:45 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

/**
 * Function to malloc and init the propertis of <t_philo> type
 * Description:
 * - The id starts at 0
 * 
 */
static int	ft_philos_init(t_program *prog)
{
	int	i;

	i = -1;
	while (++i < prog->philo_count)
	{
		prog->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!prog->philos[i])
			return (non_blocking_error_msg_ret("Failed to malloc type (t_philo *)\n", 0));
		memset(prog->philos[i], 0, sizeof(t_philo));
		prog->philos[i]->id = i;
		prog->philos[i]->start_ms = get_current_time();
		prog->philos[i]->last_meal_ms = prog->philos[i]->start_ms;
		prog->philos[i]->prog = &prog;
	}
	return (1);
}

/**
 * Function to init all the mutexes in the program
 * List of mutexes:
 * <1> mt_lock_meal
 * <2> mt_lock
 * <3> mt_forks (array of mutexes)
 */
static int	ft_sem_init(t_program *prog)
{
	sem_unlink("sem");
	prog->sem = sem_open("sem", O_CREAT, 0644, prog->philo_count);
	if (prog->sem == SEM_FAILED)
	{
		return (0);
	}
	return (1);
}

/**
 * Function to init the processes using fork() fucntion
 */
static int	ft_process_init(t_program *prog)
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
			if (pthread_create(&thread, NULL, monitor_routine, (void *) prog->philos[i]))
				return (0);
			if (pthread_detach(thread))
				return (0);
			code = philo_routine(prog->philos[i]);
			exit(code);
		}
		else
			++i;
	}
}

int	ft_init(int ac, char **av, t_program *prog)
{
	prog->ac = ac;
	prog->av = av;
	prog->philo_count = (int) ft_atold(av[1]);
	prog->time_die = ft_atold(av[2]);
	prog->time_eat = ft_atold(av[3]);
	prog->time_sleep = ft_atold(av[4]);
	if (ac == 6)
		prog->must_eat = ft_atold(av[5]);
	else
		prog->must_eat = -1;
	prog->philos = (t_philo **)
		ft_calloc((prog->philo_count + 1), sizeof(t_philo *));
	if (!prog->philos)
		return (0);
	if (!ft_sem_init(prog) || !ft_philos_init(prog))
		return (0);
	return (1);
}
