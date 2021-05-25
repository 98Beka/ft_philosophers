/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 15:10:13 by ehande            #+#    #+#             */
/*   Updated: 2021/05/23 22:08:46 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo_two.h"

void	eat(t_philo *philo)
{	
	sem_wait(philo->forks);
	print(philo->id, " has taken a left fork\n", philo);
	sem_wait(philo->forks);
	print(philo->id, " has taken a right fork\n", philo);
	print(philo->id, "eating\n", philo);
	www_stop(philo->t_to_eat);
	philo->last_t_eat = get_time_in_ms();
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	*eat_sleep_think(void *philo_void)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)philo_void;
	while (1)
	{
		eat(philo);
		i += 1;
		if (philo->must_t_to_eat != -1 && philo->must_t_to_eat == i)
			g_m_t_eat -= 1;
		print(philo->id, "sleep\n", philo);
		www_stop(philo->t_to_sleep);
		print(philo->id, "think\n", philo);
	}
	return (NULL);
}

void	*check_die(void *arg)
{
	t_philo	*philos;
	int		i;
	long	diff;

	philos = (t_philo *)arg;
	while (1)
	{
		i = -1;
		while (++i < philos[0].num_philos)
		{
			diff = get_time_in_ms() - philos[i].last_t_eat;
			if (diff > philos[0].t_to_die || !g_m_t_eat)
			{
				g_kill = 1;
				if (philos->must_t_to_eat == -1)
					printf("%lld ms %d is dead\n", \
					get_time_in_ms() - philos[i].f_time, philos[i].id);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	run_simulation(t_all *all)
{
	int			i;

	i = -1;
	g_m_t_eat = all->args[0];
	all->philos_pthread = malloc(sizeof(*all->philos_pthread) * all->args[0]);
	all->admin = malloc(sizeof(*all->admin));
	while (++i < all->args[0])
	{
		all->philos[i].f_time = get_time_in_ms();
		all->philos[i].last_t_eat = all->philos[i].f_time;
		pthread_create(&all->philos_pthread[i], \
				NULL, eat_sleep_think, (void *)&all->philos[i]);
		pthread_detach(all->philos_pthread[i]);
		usleep(100);
	}
	pthread_create(all->admin, NULL, check_die, (void *)all->philos);
	pthread_join(*all->admin, NULL);
}
