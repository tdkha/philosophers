/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:46:05 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/13 12:43:39 by ktieu            ###   ########.fr       */
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
# include <limits.h>

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
	int					*terminate;
	int					*philo_full_count;
	int					meal_eaten;
	int					must_eat;
	int					philo_count;
	size_t				last_meal_ms;
	size_t				start_ms;
	size_t				time_die;
	size_t				time_sleep;
	size_t				time_eat;
	t_thread			pth;
	t_mutex				*left_fork;
	t_mutex				*right_fork;
	t_mutex				*mt_lock;
	t_mutex				*mt_print;
}	t_philo;

typedef struct s_program
{
	int			ac;
	char		**av;
	int			terminate;
	int			philo_count;
	int			philo_full_count;
	int			must_eat;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	t_mutex		mt_lock;
	t_mutex		mt_print;
	t_mutex		*mt_forks;
	t_philo		**philos;
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

size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
int		check_dead(t_philo *philo);

//--------------------------------------------------
// PRINT MESSAGE
//--------------------------------------------------

void	error_msg(char *str, t_mutex *mt_lock);
int		error_msg_ret(char *str, t_mutex *mt_lock, int return_val);
int		philo_msg(t_philo *philo, char *str);

//--------------------------------------------------
// PROGRAM UTILS
//--------------------------------------------------

int		ft_init(int ac, char **av, t_program *prog);
int		ft_free(t_program *prog);

//--------------------------------------------------
// THREAD AND MUTEX
//--------------------------------------------------

void	*philo_routine(void *v_philo);
int		simulation(t_program *prog);

//--------------------------------------------------
// MAIN PROGRAM
//--------------------------------------------------

int		ft_arg_check(int ac, char **av);

#endif