/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 15:10:13 by ehande            #+#    #+#             */
/*   Updated: 2021/05/21 00:58:43 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo_one.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->left_f]);
	print(0, philo->id + 1, " has taken a left fork\n", philo);
	pthread_mutex_lock(&philo->forks[philo->right_f]);
	print(0, philo->id + 1, " has taken a right fork\n", philo);
	philo->last_time_eat = get_time_in_ms();
	print(philo->last_time_eat, philo->id + 1, "eating\n", philo);
	www_stop(philo->time_to_eat);
	pthread_mutex_unlock(&philo->forks[philo->left_f]);
	pthread_mutex_unlock(&philo->forks[philo->right_f]);
}

void		*eat_sleep_think(void *philo_void)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo*)philo_void;
	i = 0;
	while (i != philo->must_time_to_eat && g_kill == -1)
	{
		eat(philo);
		print(0, philo->id + 1, "sleep\n", philo);
		www_stop(philo->time_to_sleep);
		print(0, philo->id + 1, "think\n", philo);
		i++;
	}
	philo->must_time_to_eat = -2;
	return (NULL);
}


void		free_pthread(pthread_t *p, pthread_t *w, int nb)
{
	int i;

	i = -1;
	g_kill = -2;
	while (++i < nb)
		pthread_join(w[i], NULL);
	free(w);
	free(p);
}


static void	launch_philo(t_all *all, int i, t_philo *philos)
{
	if (!g_beginning)
		g_beginning = get_time_in_ms();
	while (i < all->args[0])
	{
		philos[i].last_time_eat = g_beginning;
		pthread_create(&all->philos_pthread[i], NULL, eat_sleep_think, &philos[i]);
		i += 2;
	}
}

void		run_simulation(t_all *all)
{
	int			i;

	all->philos_pthread = malloc(sizeof(*all->philos_pthread) * (all->args[0] + 1));
	all->admin_pthread = malloc(sizeof(*all->admin_pthread) * (all->args[0] + 1));
	launch_philo(all, 0, all->philos);
	if (all->args[0] % 2 == 0)
		usleep(1000);
	launch_philo(all, 1, all->philos);
	i = -1;
	while (++i < all->args[0])
		pthread_create(&all->admin_pthread[i], NULL, check_death, &all->philos[i]);
	i = -1;
	while (++i < all->args[0])
		pthread_join(all->philos_pthread[i], NULL);
	free_pthread(all->philos_pthread, all->admin_pthread, all->args[0]);
}
