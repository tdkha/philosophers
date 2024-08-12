/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:16:37 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/12 22:02:45 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
		prog->philos[i]->prog = prog;
	}
	return (1);
}

/**
 * Function to init all the semaphores
 * <1> sem_shared
 * <2> sem_forks
 * <3> sem_activate
 * <4> sem_end
 * 
 * Description: 
 * - sem_shared counter is 1 since we want only want operation at a time like printf
 * - sem_forks counter is equal to a number of forks (or philosophers)
 * - sem_activate counter is equal to a half of philosophers (odd or even scheme)
 * - sem_end is zero semaphore that will block until the sem_post() is called
 */
static int	ft_sem_init(t_program *prog)
{
	sem_unlink("shared");
	prog->sem_shared = sem_open("shared", O_CREAT, 0644, 1);
	if (prog->sem_shared == SEM_FAILED)
		return (0);
	sem_unlink("print");
	prog->sem_print = sem_open("print", O_CREAT, 0644, 1);
	if (prog->sem_print == SEM_FAILED)
		return (0);
	sem_unlink("forks");
	prog->sem_forks = sem_open("forks", O_CREAT, 0644, prog->philo_count);
	if (prog->sem_forks == SEM_FAILED)
		return (0);
	sem_unlink("activate");
	prog->sem_activate = sem_open("activate", O_CREAT, 0644, prog->philo_count / 2);
	if (prog->sem_activate == SEM_FAILED)
		return (0);
	sem_unlink("end");
	prog->sem_end = sem_open("end", O_CREAT, 0644, 0);
	if (prog->sem_end == SEM_FAILED)
		return (0);
	return (1);
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
	if (!ft_philos_init(prog))
		return (0);
	if (!ft_sem_init(prog))
	{
		ft_philos_clean(prog);
		return (0);
	}
	return (1);
}
