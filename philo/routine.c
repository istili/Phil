/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:11:26 by istili            #+#    #+#             */
/*   Updated: 2024/09/11 13:51:49 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->ptr->forks[philo->l_fork]);
	print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->ptr->forks[philo->r_fork]);
	print(philo, "has taken a fork");
	print(philo, "is eating");
	update_time(&philo->time_mutex, &philo->last_meal_time, time_in_ms());
	update_int(&philo->meals_mutex, &philo->meals_eaten,
		read_int(&philo->meals_mutex, &philo->meals_eaten) + 1);
	ft_sleep(philo->ptr->eat);
	pthread_mutex_unlock(&philo->ptr->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->ptr->forks[philo->r_fork]);
}

void	*fthread(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (read_int(&philo->ptr->int_mutex, &philo->ptr->start) != 1)
		usleep(10);
	update_time(&philo->time_mutex, &philo->last_meal_time,
		read_time(&philo->ptr->int_mutex, &philo->ptr->start_time));
	if (!(philo->id % 2))
		ft_sleep(philo->ptr->eat / 2);
	while (1)
	{
		eating(philo);
		print(philo, "is sleeping");
		ft_sleep(philo->ptr->sleep);
		print(philo, "is thinking");
	}
	return (NULL);
}
