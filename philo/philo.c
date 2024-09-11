/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:42:42 by istili            #+#    #+#             */
/*   Updated: 2024/09/11 11:39:40 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	creating_philos(t_main *p)
{
	int	i;

	i = 0;
	while (p->n_philo > i)
	{
		if (pthread_create(&p->arr[i].th, NULL,
				fthread, (void *)&p->arr[i]) != 0)
		{
			ft_destroy(p, 3, 3, p->n_philo);
			return (error(ERR_TH), 1);
		}
		i++;
	}
	return (0);
}

static void	fill(t_main *p, int *i)
{
	p->arr[*i].ptr = p;
	p->arr[*i].id = *i + 1;
	p->arr[*i].l_fork = *i;
	p->arr[*i].r_fork = *i + 1;
	if (*i == p->n_philo - 1)
		p->arr[*i].r_fork = 0;
	p->arr[*i].meals_eaten = 0;
	p->arr[*i].is_full = 0;
}

int	init_philos(t_main *p)
{
	int				i;

	i = 0;
	while (p->n_philo > i)
	{
		fill(p, &i);
		if (pthread_mutex_init(&p->forks[i], NULL) != 0)
		{
			ft_destroy(p, 3, 1, i);
			return (error(ERR_FORK), 1);
		}
		if (pthread_mutex_init(&p->arr[i].time_mutex, NULL) != 0)
		{
			ft_destroy(p, 3, 2, i);
			return (error(ERR_TIME), 1);
		}
		if (pthread_mutex_init(&p->arr[i].meals_mutex, NULL) != 0)
		{
			ft_destroy(p, 3, 3, i);
			return (error(ERR_MEALS), 1);
		}
		i++;
	}
	return (0);
}

int	creating_mutexs(t_main *p)
{
	int				i;

	i = 0;
	if (pthread_mutex_init(&p->int_mutex, NULL) != 0)
	{
		ft_destroy(p, 1, 0, i);
		return (error(ERR_INT), 1);
	}
	if (pthread_mutex_init(&p->print_mutex, NULL) != 0)
	{
		ft_destroy(p, 2, 0, i);
		return (error(ERR_PRINT), 1);
	}
	return (0);
}

int	allocating(t_main *p)
{
	p->forks = malloc(sizeof(pthread_mutex_t) * p->n_philo);
	if (!p->forks)
		return (error(ERR_MALLOC), 1);
	ft_memset(p->forks, 0, sizeof(pthread_mutex_t));
	p->arr = malloc(sizeof(t_philo) * p->n_philo);
	if (!p->arr)
	{
		ft_destroy(p, 0, 0, 0);
		return (error(ERR_MALLOC), 1);
	}
	ft_memset(p->arr, 0, sizeof(t_philo));
	return (0);
}
