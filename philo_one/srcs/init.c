/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:06:22 by ehande            #+#    #+#             */
/*   Updated: 2021/05/23 20:55:25 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo_one.h"

static	void	get_philos_data(t_all *all, t_philo *philos, int i)
{
	philos->id = i + 1;
	philos->num_philos = all->args[0];
	philos->last_t_eat = 0;
	philos->t_to_die = all->args[1];
	philos->t_to_eat = all->args[2];
	philos->t_to_sleep = all->args[3];
	philos->must_t_to_eat = all->args[4];
	philos->left_f = &all->forks[i];
	philos->right_f = &all->forks[i + 1];
	if (i == all->args[0] - 1)
		philos->right_f = &all->forks[0];
}

void	init(t_all *all)
{
	int	i;

	all->philos = malloc(sizeof(*all->philos) * all->args[0]);
	all->print = malloc(sizeof(*all->print));
	pthread_mutex_init(all->print, NULL);
	i = -1;
	all->forks = malloc(sizeof(*all->forks) * all->args[0]);
	while (++i < all->args[0])
		pthread_mutex_init(&all->forks[i], NULL);
	i = -1;
	while (++i < all->args[0])
	{
		get_philos_data(all, &all->philos[i], i);
		all->philos[i].print = all->print;
	}	
}
