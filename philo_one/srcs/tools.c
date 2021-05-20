/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 15:22:30 by ehande            #+#    #+#             */
/*   Updated: 2021/05/20 20:07:06 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo_one.h"

int		get_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int		get_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*check_death(void *philo)
{
	t_philo		*ph;
	long long	diff;
	long long	real_time;
	
	ph = (t_philo*)philo;
	while (g_kill == -1)
	{
		real_time = get_time_in_ms();
		diff = real_time - ph->last_time_eat;
		if ((diff >= ph->time_to_die && ph->must_time_to_eat != -2) || g_kill != -1)
		{
			if (g_kill == -1)
				print(real_time, ph->id + 1, "died\n", ph);
			g_kill = ph->id;
			break ;
		}
	}
	return (NULL);
}

void	www_stop(long long time)
{
	long long start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < time)
		usleep(400);
}