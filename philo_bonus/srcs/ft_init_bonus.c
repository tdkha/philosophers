/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:16:37 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/15 16:37:47 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	ft_make_sem_name(t_philo *philo, int id, int i, int j)
{
	int		len;
	char	temp;

	len = 0;
	philo->sem_name[i++] = 'p';
	philo->sem_name[i++] = 'h';
	philo->sem_name[i++] = 'i';
	philo->sem_name[i++] = 'l';
	philo->sem_name[i++] = 'o';

	if (id == 0)
	{
		philo->sem_name[i++] = '0';
		philo->sem_name[i] = '\0';
		return;
	}

	while (id > 0)
	{
		philo->sem_name[i + len] = (id % 10) + '0';
		id /= 10;
		++len;
	}

	// Reverse the digits to correct the order
	while (j < len / 2)
	{
		temp = philo->sem_name[i + j];
		philo->sem_name[i + j] = philo->sem_name[i + len - 1 - j];
		philo->sem_name[i + len - 1 - j] = temp;
		j++;
	}

	philo->sem_name[i + len] = '\0';
}

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
			return (error_msg_ret(
				"philo_bonus: ft_philos_init: malloc()\n", 0));
		memset(prog->philos[i], 0, sizeof(t_philo));
		memset(prog->philos[i]->sem_name, 0, 80);
		prog->philos[i]->id = i;
		prog->philos[i]->start_ms = get_current_time();
		prog->philos[i]->last_meal_ms = prog->philos[i]->start_ms;
		prog->philos[i]->prog = prog;
		ft_make_sem_name(prog->philos[i], i, 0, 0);
		sem_unlink(prog->philos[i]->sem_name);
		prog->philos[i]->sem_terminate = sem_open(prog->philos[i]->sem_name, O_CREAT, 0644, 1);
		if (prog->philos[i]->sem_terminate == SEM_FAILED)
			return (error_msg_ret(
				"philo_bonus: ft_philos_init: sem_open()\n", 0));
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
	prog->sem_activate = sem_open(
			"activate", O_CREAT, 0644, (prog->philo_count + 1)/ 2);
	if (prog->sem_activate == SEM_FAILED)
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
