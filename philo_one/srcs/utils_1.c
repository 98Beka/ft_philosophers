/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:36:30 by ehande            #+#    #+#             */
/*   Updated: 2021/05/07 19:00:53 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		msp(const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	return (i);
}

int				ft_atoi(const char *str)
{
	unsigned long int	res;
	int					i;
	int					sb;

	sb = 1;
	res = 0;
	i = msp(str);
	if (str[i] == '-')
	{
		i++;
		sb = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res > 2147483647 && sb == 1)
		return (-1);
	if (res > 2147483648 && sb == -1)
		return (0);
	return (res * sb);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t w(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

void finish(char *str)
{
	w(str);
	exit(0);
}