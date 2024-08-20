/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:16:37 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/20 08:35:46 by ktieu            ###   ########.fr       */
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
	int		i;

	i = -1;
	while (++i < prog->philo_count)
	{
		prog->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!prog->philos[i])
			return (error_msg_ret("ft_philos_init: malloc\n", 0));
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
 * 
 * Description: 
 * - sem_shared counter is set to 1
 * - sem_forks counter is equal to a number of forks (or philosophers)
 * - sem_activate counter is equal to a half of philosophers (odd or even scheme)
 */
static int	ft_sem_init(t_program *prog)
{
	sem_unlink("philo_shared");
	prog->sem_shared = sem_open("philo_shared", O_CREAT, 0644, 1);
	if (prog->sem_shared == SEM_FAILED)
		return (0);
	sem_unlink("philo_print");
	prog->sem_print = sem_open("philo_print", O_CREAT, 0644, 1);
	if (prog->sem_print == SEM_FAILED)
		return (0);
	sem_unlink("philo_forks");
	prog->sem_forks = sem_open("philo_forks", O_CREAT, 0644, prog->philo_count);
	if (prog->sem_forks == SEM_FAILED)
		return (0);
	sem_unlink("philo_activate");
	prog->sem_activate = sem_open(
			"philo_activate", O_CREAT, 0644, (prog->philo_count + 1) / 2);
	if (prog->sem_activate == SEM_FAILED)
		return (0);
	sem_unlink("philo_terminate");
	prog->sem_terminate = sem_open(
			"philo_terminate", O_CREAT, 0644, 1);
	if (prog->sem_terminate == SEM_FAILED)
		return (0);
	return (1);
}

/**
 * Quickly die if time die is smaller than the others
 */
static void	reassign_time(t_program *prog)
{
	if (prog->time_eat > prog->time_die)
	{
		prog->time_eat = prog->time_die + 6;
	}
	if (prog->time_sleep > prog->time_die)
	{
		prog->time_sleep = prog->time_die + 6;
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
	reassign_time(prog);
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
