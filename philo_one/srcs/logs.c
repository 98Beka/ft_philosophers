/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 15:20:27 by ehande            #+#    #+#             */
/*   Updated: 2021/05/20 21:05:48 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo_one.h"

static	int	nb_length(unsigned long n)
{
	int	count;

	count = 1;
	while (n >= 10)
	{
		n = n / 10;
		count = count + 1;
	}
	return (count);
}

static	int	ft_itoa_on_buffer(unsigned long timestamp, char *str)
{
	int nb_len;
	int index;

	nb_len = nb_length(timestamp);
	index = --nb_len;
	while (nb_len >= 0)
	{
		str[nb_len] = timestamp % 10 + '0';
		timestamp /= 10;
		nb_len--;
	}
	return (index);
}

void		print(long long time, int id, char *log, t_philo *philo)
{
	char		str[100];
	int			index;

	if (g_kill != -1)
		return ;
	pthread_mutex_lock(philo->print);
	if (!time)
		time = get_time_in_ms() - g_beginning;
	else
		time -= g_beginning;
	index = ft_itoa_on_buffer(time, str);
	index++;
	str[index++] = ' ';
	index += ft_itoa_on_buffer(id, &str[index]);
	index++;
	str[index++] = ' ';
	ft_strcpy(&str[index], log);
	if (g_kill == -1)
		write(1, str, ft_strlen(str));
	pthread_mutex_unlock(philo->print);
}
