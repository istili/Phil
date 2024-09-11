/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 01:33:02 by istili            #+#    #+#             */
/*   Updated: 2024/09/11 13:13:49 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	read_time(pthread_mutex_t *mutex, long *time)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *time;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	update_time(pthread_mutex_t *mutex, long *time, long new_time)
{
	pthread_mutex_lock(mutex);
	*time = new_time;
	pthread_mutex_unlock(mutex);
}

void	ft_sleep(long time_to_sleep)
{
	long	start_time;

	start_time = time_in_ms();
	while (time_in_ms() - start_time < time_to_sleep)
		usleep(500);
}

static int	watcher(t_main *p, int *i, int nb_philo_full)
{
	long	time;

	if (nb_philo_full == p->n_philo)
	{
		pthread_mutex_lock(&p->print_mutex);
		return (0);
	}
	time = time_in_ms();
	if (time - read_time(&p->arr[*i].time_mutex,
			&p->arr[*i].last_meal_time) >= p->die)
	{
		print(&p->arr[*i], "is dead");
		pthread_mutex_lock(&p->print_mutex);
		return (0);
	}
	return (1);
}

int	watching_dead(t_main *p)
{
	int		i;
	int		nb_philo_full;

	ft_sleep(p->die / 2);
	nb_philo_full = 0;
	while (1)
	{
		i = 0;
		while (i < p->n_philo)
		{
			if (p->max_meals != -1 && !p->arr[i].is_full
				&& read_int(&p->arr[i].meals_mutex,
					&p->arr[i].meals_eaten) >= p->max_meals)
			{
				nb_philo_full++;
				p->arr[i].is_full = 1;
			}
			if (!watcher(p, &i, nb_philo_full))
				return (0);
			i++;
		}
	}
}
