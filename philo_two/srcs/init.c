/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:06:22 by ehande            #+#    #+#             */
/*   Updated: 2021/05/23 19:55:37 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo_two.h"

static	void	get_philos_data(t_all *all, t_philo *philos, int i)
{
	philos->id = i + 1;
	philos->num_philos = all->args[0];
	philos->last_t_eat = 0;
	philos->t_to_die = all->args[1];
	philos->t_to_eat = all->args[2];
	philos->t_to_sleep = all->args[3];
	philos->must_t_to_eat = all->args[4];
}

void	init(t_all *all)
{
	int	i;

	sem_unlink("/fork");
	sem_unlink("/print");
	all->philos = malloc(sizeof(*all->philos) * all->args[0]);
	all->print = sem_open("/print", O_CREAT, 0666, 1);
	all->forks = sem_open("/fork", O_CREAT, 0666, all->args[0]);
	i = -1;
	while (++i < all->args[0])
	{
		all->philos[i].forks = all->forks;
		get_philos_data(all, &all->philos[i], i);
		all->philos[i].print = all->print;
	}
}
