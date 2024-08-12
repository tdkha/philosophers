/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:16:59 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/12 23:12:51 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static t_program	*ft_prog_init(void)
{
	t_program	*res;

	res = (t_program *)ft_calloc(1, sizeof(t_program));
	if (!res)
	{
		error_msg("Malloc failed for type (t_prog *)\n");
		exit(1);
	}
	memset(res, 0, sizeof(t_program));
	return (res);
}

int	main(int ac, char **av)
{
	t_program	*prog;

	if ((ac != 5 && ac != 6) || !ft_arg_check(ac, av))
	{
		error_msg("Invalid argument(s)\n");
		exit(1);
	}
	prog = ft_prog_init();
	if (!ft_init(ac, av, prog) || !create_process(prog))
	{
		ft_free(prog);
		exit(1);
	}
	wait_process(prog);
	ft_free(prog);
	return (0);
}
