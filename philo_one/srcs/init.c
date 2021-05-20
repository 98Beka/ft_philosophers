/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:06:22 by ehande            #+#    #+#             */
/*   Updated: 2021/05/20 21:05:30 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo_one.h"

static void	exchange(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static	void	get_philos_data(t_all *all, t_philo *philos, int i)
{
	philos->id = i;
	philos->last_time_eat = 0;
	philos->time_to_die = all->args[1];
	philos->time_to_eat = all->args[2];
	philos->time_to_sleep = all->args[3];
	philos->must_time_to_eat = all->args[5];
	philos->left_f = i;
	philos->right_f = i + 1;
	if (i == all->args[0] - 1)
	{
		philos->right_f = 0;
		exchange(&philos->left_f, &philos->right_f);
	}
	if (all->args[0] % 2 && philos->id == all->args[0] - 1)
		exchange(&philos->left_f, &philos->right_f);
	if (all->args[0] % 2 && philos->id % 2)
		exchange(&philos->left_f, &philos->right_f);
}

void			init(t_all *all)
{
	int	i;
	int j;
	
	i = -1;
	g_kill = -1;
	all->philos = malloc(sizeof(*all->philos) * all->args[0]);
	all->admin = malloc(sizeof(*all->admin));
	pthread_mutex_init(all->admin, NULL);
	i = -1;
	while (++i < all->args[0])
	{
		j = -1;
		all->philos[i].forks = malloc(sizeof(*all->philos[i].forks) * all->args[0]);
		while (++j < all->args[0])
			pthread_mutex_init(&all->philos->forks[j], NULL);
		get_philos_data(all, &all->philos[i], i);
		all->philos[i].print = all->admin;
	}
}