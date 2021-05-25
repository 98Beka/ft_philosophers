/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 15:20:27 by ehande            #+#    #+#             */
/*   Updated: 2021/05/23 21:25:20 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo_one.h"

static	int	nb_l(unsigned long n)
{
	int	count;

	count = 1;
	while (n >= 10)
	{
		n = n / 10;
		count += 1;
	}
	return (count);
}

static	int	ft_itoa_bf(unsigned long timestamp, char *str)
{
	int	l;
	int	index;

	l = nb_l(timestamp);
	index = --l;
	while (l >= 0)
	{
		str[l] = timestamp % 10 + '0';
		timestamp /= 10;
		l--;
	}
	return (index);
}

void	print(int id, char *log, t_philo *philo)
{
	char		str[1000];
	long long	time;
	int			index;

	if (g_kill)
		return ;
	pthread_mutex_lock(philo->print);
	time = get_time_in_ms() - philo->f_time;
	index = ft_itoa_bf(time, str);
	index++;
	str[index++] = ' ';
	str[index++] = 'm';
	str[index++] = 's';
	str[index++] = ' ';
	str[index++] = ' ';
	index += ft_itoa_bf(id, &str[index]);
	index++;
	str[index++] = ' ';
	ft_strcpy(&str[index], log);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(philo->print);
}
