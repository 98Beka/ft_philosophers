/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:28:27 by ehande            #+#    #+#             */
/*   Updated: 2021/05/22 20:23:37 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo_one.h"

static void	pars(char **arg, int argc, t_all *all)
{
	int	i;
	int	n;

	i = 0;
	if (argc > 6 || argc < 5)
		finish(ERR_NUM_ARGS);
	while (arg[++i])
	{
		n = -1;
		if (arg[i][0] == '-')
			finish("Arguments cannot be negative\n");
		while (arg[i][++n])
			if (arg[i][n] < '0' || arg[i][n] > '9')
				finish("Arguments must be numbers\n");
	}
	i = -1;
	while (arg[++i + 1])
		all->args[i] = ft_atoi(arg[i + 1]);
	if (i < 5)
		all->args[4] = -1;
}

int	main(int argc, char **argv)
{
	t_all	all;

	g_kill = 0;
	pars(argv, argc, &all);
	init(&all);
	run_simulation(&all);
	free(all.philos);
	free(all.print);
	free(all.forks);
	free(all.philos_pthread);
	free(all.admin);
	return (0);
}
