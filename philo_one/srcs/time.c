/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 15:19:26 by ehande            #+#    #+#             */
/*   Updated: 2021/05/10 20:54:55 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo_one.h"

long long	get_time_in_ms()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
