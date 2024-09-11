/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:45:12 by istili            #+#    #+#             */
/*   Updated: 2024/09/11 08:49:36 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	convert(int sec)
{
	long long	msec;

	msec = (sec + 500) / 100;
	return (msec);
}

long	time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->ptr->print_mutex);
	printf("%ld %d %s\n", time_in_ms() - philo->ptr->start_time,
		philo->id, msg);
	pthread_mutex_unlock(&philo->ptr->print_mutex);
}

int	read_int(pthread_mutex_t *mutex, int *nb)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *nb;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	update_int(pthread_mutex_t *mutex, int *nb, int new)
{
	pthread_mutex_lock(mutex);
	*nb = new;
	pthread_mutex_unlock(mutex);
}
