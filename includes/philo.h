/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:46:05 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/24 10:34:18 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

//--------------------------------------------------
// RE_DEFINITION
//--------------------------------------------------

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

//--------------------------------------------------
// STRUCT
//--------------------------------------------------

typedef enum s_clean_code
{
	ALL,
	PHILO,
	MUTEX
}	t_clean_code;

typedef enum s_philo_status
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_philo_status;

typedef enum s_mutex_code
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mutex_code;

typedef enum s_thread_code
{
	CREATE,
	JOIN
}	t_thead_code;

typedef struct s_philo
{
	int					id;
	size_t				last_meal_ms;
	long				meal_eaten;
	t_philo_status			status;
	t_thread			pth;
	struct s_program	*prog;
}	t_philo;

typedef struct s_program
{
	int			ac;
	char		**av;
	int			philo_count;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	t_mutex		mt_lock_meal;
	t_mutex		mt_lock_print;
	t_mutex		mt_lock_dead;
	t_mutex		*mt_forks;
	t_philo		**philos;
	t_thread	*pth_monitor;
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
// PRINT MESSAGE
//--------------------------------------------------

void	error_msg(t_program *prog, char *str);
int		error_msg_ret(t_program *prog, char *str, int return_val);

void	philo_msg(t_philo *philo, t_philo_status status);

//--------------------------------------------------
// PROGRAM UTILS
//--------------------------------------------------

int		ft_init(int ac, char **av, t_program *prog);

int		ft_mutexes_clean(t_program *prog);
int		ft_philos_clean(t_program *prog);
int		ft_clean(t_program *prog, t_clean_code code);

int		ft_free(t_program *prog);

//--------------------------------------------------
// THREAD AND MUTEX
//--------------------------------------------------

int		ft_mutex(
			t_mutex *mutex,
			t_mutex_code code,
			t_program *prog);
int		ft_thread(
			t_thread *thread,
			void *(*func)(void *),
			void *arg,
			t_thead_code code);

//--------------------------------------------------
// MAIN PROGRAM
//--------------------------------------------------

int		ft_arg_check(int ac, char **av);
int		philosopher(t_program *prog);

#endif