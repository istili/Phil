/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 01:33:02 by istili            #+#    #+#             */
/*   Updated: 2024/08/26 06:33:48 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	philo(int nb_philo, int time_die, int time_eat, int time_sleep)
// void	philo(char *args)

int	convert(int sec)
{
	long long msec = (sec + 500) / 100;
	return (msec);
}

long	time_in_ms()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void	print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->ptr->print_mutex);
	printf("%ld %d %s\n", time_in_ms() - philo->ptr->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->ptr->print_mutex);
}

int		read_int(pthread_mutex_t *mutex, int *nb)
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

long	read_time(pthread_mutex_t *mutex, long *time)
{
	long ret;

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

void	ft_sleep(long time)
{
	long start_time = time_in_ms();
	while (time_in_ms() - start_time < time)
		usleep(500);
}

void	*fthread(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (read_int(&philo->ptr->int_mutex, &philo->ptr->start) != 1)
		usleep(10);
	update_time(&philo->time_mutex, &philo->last_meal_time, read_time(&philo->ptr->int_mutex, &philo->ptr->start_time));
	if (!(philo->id % 2))
		ft_sleep(philo->ptr->eat / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->ptr->forks[philo->l_fork]);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->ptr->forks[philo->r_fork]);
		print(philo, "has taken a fork");
		print(philo, "is eating");
		update_time(&philo->time_mutex, &philo->last_meal_time, time_in_ms());
		update_int(&philo->meals_mutex, &philo->meals_eaten, read_int(&philo->meals_mutex, &philo->meals_eaten) + 1);
		ft_sleep(philo->ptr->eat);
		pthread_mutex_unlock(&philo->ptr->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->ptr->forks[philo->r_fork]);
		print(philo, "is sleeping");
		ft_sleep(philo->ptr->sleep);
		print(philo, "is thinking");
	}
	return (NULL);
}

int	l7day(t_main *p)
{
	int	i;
	int	nb_philo_full;

	ft_sleep(p->die / 2);
	nb_philo_full = 0;
	while (1)
	{
		i = 0;
		while (i < p->n_philo)
		{
			if (p->max_meals != -1 && !p->arr[i].is_full && read_int(&p->arr[i].meals_mutex, &p->arr[i].meals_eaten) >= p->max_meals)
			{
				nb_philo_full++;
				p->arr[i].is_full = 1;
			}
			if (nb_philo_full == p->n_philo)
			{
				pthread_mutex_lock(&p->print_mutex);
				return (0);
			}
			long time = time_in_ms();
			if (time - read_time(&p->arr[i].time_mutex, &p->arr[i].last_meal_time) >= p->die)
			{
				print(&p->arr[i], "is dead");
				pthread_mutex_lock(&p->print_mutex);
				return (0);
			}
			i++;
		}
	}
}

void	philo(t_main *p)
{
	int				i;

	i = 0;
	p->forks = malloc(sizeof(pthread_mutex_t) * p->n_philo);
	if (!p->forks)
		return ;
	ft_memset(p->forks, 0, sizeof(pthread_mutex_t));
	p->arr = malloc(sizeof(t_philo) * p->n_philo);
	if (!p->arr)
		return ;
	ft_memset(p->arr, 0, sizeof(t_philo));
	if (pthread_mutex_init(&p->int_mutex, NULL) != 0)
	{
		printf("error int mutex\n");
		return ;
	}
	if (pthread_mutex_init(&p->print_mutex, NULL) != 0)
	{
		printf("error print mutex\n");
		return ;
	}
	while (p->n_philo > i)
	{
		p->arr[i].ptr = p;
		p->arr[i].id = i + 1;
		p->arr[i].l_fork = i;
		p->arr[i].r_fork = i + 1;
		if (i == p->n_philo - 1)
			p->arr[i].r_fork = 0;
		p->arr[i].meals_eaten = 0;
		p->arr[i].is_full = 0;
		if (pthread_mutex_init(&p->forks[i], NULL) != 0)
		{
			printf("error mutex %d\n", i);
			return ;
		}
		if (pthread_mutex_init(&p->arr[i].time_mutex, NULL) != 0)
		{
			printf("error time mutex %d\n", i);
			return ;
		}
		if (pthread_mutex_init(&p->arr[i].meals_mutex, NULL) != 0)
		{
			printf("error meals mutex %d\n", i);
			return ;
		}
		i++;
	}
	p->start = 0;
	i = 0;
	while (p->n_philo > i)
	{
		if (pthread_create(&p->arr[i].th, NULL, fthread, (void *)&p->arr[i]) != 0)
		{
			printf("error creating thread %d\n", i);
			return ;
		}
		i++;
	}
	update_time(&p->int_mutex, &p->start_time, time_in_ms());
	update_int(&p->int_mutex, &p->start, 1);
	i = 0;
	while (p->n_philo > i)
	{
		if (pthread_detach(p->arr[i].th) != 0)
			return ;
		i++;
	}
	l7day(p);
	i = 0;
	while (p->n_philo > i)
	{
		pthread_mutex_destroy(&p->forks[i]);
		i++;
	}
	free(p->forks);
	free(p->arr);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 5)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	(void)ac;
	// char	**split_args;
	// char	*arr;
	// int		i;

	// arr = NULL;
	// split_args = NULL;
	// i = 1;
	// while (ac > i)
	// {
	// 	if (av[i][0] == '\0' || is_full_space(av[i]))
	// 	{
	// 		if (arr)
	// 			free(arr);
	// 		ft_puterror();
	// 	}
	// 	arr = ft_strjoin(arr, av[i++]);
	// 	if (!arr)
	// 		ft_puterror();
	// }
	// split_args = ft_split(arr, ' ');
	// if (!split_args)
	// 	ft_puterror();
	// free(arr);
	// i = 0;
	// while (split_args[i])
	// {
	// 	if (!ft_strcmp(split_args[i], "-2147483648")
	// 		|| !ft_strcmp(split_args[i], "2147483647"))
	// 		ft_puterror();
	// 	if (args(split_args[i]) == 0)
	// 	{
	// 		free_array(split_args);
	// 		ft_puterror();
	// 	}
	// 	// printf("here: %s\n", split_args[i]);
	// 	i++;
	// }
	// if (!count_args(split_args))
	// 	ft_puterror();
	// if (split_args[0] == 0)
	// 	ft_puterror();
	t_main	p;
	p.n_philo = ft_atoi(av[1]);
	p.die = ft_atoi(av[2]);
	p.eat = ft_atoi(av[3]);
	p.sleep = ft_atoi(av[4]);
	p.max_meals = -1;
	if (ac == 6)
		p.max_meals = ft_atoi(av[5]);
	philo(&p);
	return 0;
}
