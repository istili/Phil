/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:36:48 by istili            #+#    #+#             */
/*   Updated: 2024/09/11 13:03:57 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo(t_main *p)
{
	int				i;

	i = 0;
	if (allocating(p))
		return ;
	if (creating_mutexs(p))
		return ;
	if (init_philos(p))
		return ;
	p->start = 0;
	if (creating_philos(p))
		return ;
	update_time(&p->int_mutex, &p->start_time, time_in_ms());
	update_int(&p->int_mutex, &p->start, 1);
	while (p->n_philo > i)
	{
		if (pthread_detach(p->arr[i].th) != 0)
		{
			ft_destroy(p, 3, 3, p->n_philo);
			return ;
		}
		i++;
	}
	watching_dead(p);
	ft_destroy(p, 3, 3, p->n_philo);
}

int	main(int ac, char **av)
{
	t_main	p;

	if (parsing(ac, av))
		return (error(ERR_PARSING), 1);
	p.n_philo = ft_atoi(av[1]);
	p.die = ft_atoi(av[2]);
	p.eat = ft_atoi(av[3]);
	p.sleep = ft_atoi(av[4]);
	p.max_meals = -1;
	if (ac == 6)
		p.max_meals = ft_atoi(av[5]);
	if (p.n_philo == 0)
		return (0);
	philo(&p);
	return (0);
}
