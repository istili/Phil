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

void	*pthread(void)
{
	printf("here\n");
	return (NULL);
}

void	philo(int n_phil, int time_to_die, int time_to_eat, int time_to_sleep)
{
	pthread_t		id;
	int				i;
	int				*ids[n_phil];
	(void)time_to_die;
	(void)time_to_eat;
	(void)time_to_sleep;

	i = 0;
	while (n_phil > i)
	{
		pthread_create(&id, NULL, pthread(), &ids[n_phil]);
		i++;
	}
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
	char	**split_args;
	char	*arr;
	int		i;

	arr = NULL;
	split_args = NULL;
	i = 1;
	while (ac > i)
	{
		if (av[i][0] == '\0' || is_full_space(av[i]))
		{
			if (arr)
				free(arr);
			ft_puterror();
		}
		arr = ft_strjoin(arr, av[i++]);
		if (!arr)
			ft_puterror();
	}
	split_args = ft_split(arr, ' ');
	if (!split_args)
		ft_puterror();
	free(arr);
	i = 0;
	while (split_args[i])
	{
		if (!ft_strcmp(split_args[i], "-2147483648")
			|| !ft_strcmp(split_args[i], "2147483647"))
			ft_puterror();
		if (args(split_args[i]) == 0)
		{
			free_array(split_args);
			ft_puterror();
		}
		// printf("here: %s\n", split_args[i]);
		i++;
	}
	if (!count_args(split_args))
		ft_puterror();
	if (split_args[0] == 0)
		ft_puterror();
	int	number_of_philosophers = ft_atoi(split_args[0]);
	int	time_to_die = ft_atoi(split_args[1]);
	int time_to_eat = ft_atoi(split_args[2]);
	int time_to_sleep = ft_atoi(split_args[3]);
	philo(number_of_philosophers, time_to_die, time_to_eat, time_to_sleep);
	return 0;
}
