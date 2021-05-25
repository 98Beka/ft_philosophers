/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 15:10:13 by ehande            #+#    #+#             */
/*   Updated: 2021/05/25 04:48:47 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo_three.h"

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
	philo->m_t_eat = 0;
	while (1)
	{
		eat(philo);
		i += 1;
		if (philo->must_t_to_eat != -1 && philo->must_t_to_eat == i)
			philo->m_t_eat = 1;
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
		while (++i < philos->num_philos)
		{
			diff = get_time_in_ms() - philos->last_t_eat;
			if (philos->m_t_eat)
				exit(3);
			if (diff > philos->t_to_die && !philos->m_t_eat)
			{
				// g_kill = 1;
				printf("%lld ms %d is dead\n", \
				get_time_in_ms() - philos->f_time, philos->id);
				exit(2);
			}
		}
	}
	return (NULL);
}

static void	kill_philos(t_all *all)
{
	int	i;
	int	status;

	i = -1;
	waitpid(-1, &status, 0);
	status = WEXITSTATUS(status);
	if (status == 3)
		while (++i < all->args[0])
			wait(&all->pid[i]);
	if (status != 0)
		while (++i < all->args[0])
			kill(all->pid[i], SIGKILL);
}

void	run_simulation(t_all *all)
{
	int		i;

	i = -1;
	all->philos_pthread = malloc(sizeof(*all->philos_pthread) * all->args[0]);
	all->admin = malloc(sizeof(*all->admin));
	all->pid = malloc(sizeof(pid_t) * all->args[0]);
	while (++i < all->args[0])
	{
		all->philos[i].f_time = get_time_in_ms();
		all->philos[i].last_t_eat = all->philos[i].f_time;
		all->pid[i] = fork();
		if (!all->pid[i])
		{
			pthread_create(all->admin, NULL, \
					eat_sleep_think, (void *)(&(all->philos[i])));
			pthread_create(&all->philos_pthread[i], NULL, \
					check_die, (void *)(&(all->philos[i])));
			pthread_detach(all->philos_pthread[i]);
			pthread_join(*all->admin, NULL);
		}
		usleep(100);
	}
	kill_philos(all);
}
