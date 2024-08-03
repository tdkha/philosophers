/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:45:26 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/03 16:26:39 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// static void	error_msg_no_lock(char *str)
// {
// 	int	len;

// 	len = (int) ft_strlen(str);
// 	(void)!write(2, str, len);
// }

int	main(int ac, char **av)
{
	t_program	prog;

	memset(&prog, 0, sizeof(t_program));
	if ((ac != 5 && ac != 6) || !ft_arg_check(ac, av))
	{
		error_msg("Invalid argument(s)\n", &prog.mt_lock_print);
		exit(1);
	}
	if (ft_init(ac, av, &prog) == 0)
	{
		ft_free(&prog);
		exit(1);
	}
	if (simulation(&prog) == 0)
	{
		ft_free(&prog);
		exit(1);
	}
	ft_free(&prog);
	return (0);
}
