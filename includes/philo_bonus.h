/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:46:05 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/07 08:08:34 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <limits.h>
# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>

//--------------------------------------------------
// RE_DEFINITION
//--------------------------------------------------

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

//--------------------------------------------------
// STRUCT
//--------------------------------------------------

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	int					meal_eaten;
	int					philo_count;
	size_t				last_meal_ms;
	size_t				start_ms;
	struct s_program	*prog;
}	t_philo;

/**
 * Struct for a shared data in a program
 * @param ac argument count
 * @param av argument vector
 * @param philo_count a total number of philosophers
 * @param must_eat a number of meals one philisopher should eat (if specified)
 * @param time_die interval for lifespan if not eating
 * @param time_eat tike for eating
 * @param time_sleep time for sleeping
 * @param philos array of philosophers
 * @param sem_shared a shared semaphore to be used among general functions
 * @param sem_forks a semephore that represents forks for n philosophers
 * @param sem_activated a semaphore that represents the currently acivated philosophers
 * @param sem_end a zero semaphore used to notify the end of the program
 * 
 */
typedef struct s_program
{
	int			ac;
	char		**av;
	int			philo_count;
	int			must_eat;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	t_philo		**philos;
	sem_t		*sem_shared;
	sem_t		*sem_forks;
	sem_t		*sem_activate;
	sem_t		*sem_end;
}	t_program;

//--------------------------------------------------
// LIBFT
//--------------------------------------------------

int		ft_isdigit(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *s);
long	ft_atold(const char *str);
void	*ft_calloc(size_t count, size_t size);

//--------------------------------------------------
// UTILS
//--------------------------------------------------

size_t	get_current_time();
int		ft_usleep(size_t milliseconds);
int		check_dead(t_philo *philo);
int		ft_min(int a, int b);
int		ft_max(int a, int b);

//--------------------------------------------------
// PRINT MESSAGE
//--------------------------------------------------

void	non_blocking_error_msg(char *str);
int		non_blocking_error_msg_ret(char *str, int val);
void	error_msg(char *str, sem_t *sem_shared);
int		error_msg_ret(char *str, sem_t *sem_shared, int return_val);
int		philo_msg(t_philo *philo, char *str);

//--------------------------------------------------
// PROGRAM UTILS
//--------------------------------------------------

int		ft_init(int ac, char **av, t_program *prog);
int		ft_free(t_program *prog);

//--------------------------------------------------
// THREAD AND MUTEX
//--------------------------------------------------

int		philo_routine(t_philo *philo);
void	*monitor_routine(void *v_philo);
// int		simulation(t_program *prog);

//--------------------------------------------------
// MAIN PROGRAM
//--------------------------------------------------

int		ft_arg_check(int ac, char **av);

#endif