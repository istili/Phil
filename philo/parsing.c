/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:39:15 by istili            #+#    #+#             */
/*   Updated: 2024/09/11 13:02:21 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *s)
{
	write(1, s, ft_strlen(s));
	return ;
}

static int	is_full_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

static int	args(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int	parsing(int ac, char **av)
{
	int		i;

	i = 1;
	if (ac == 5 || ac == 6)
	{
		while (av[i])
		{
			if (av[i][0] == '\0' || is_full_space(av[i]))
				return (1);
			if (args(av[i]) == 0)
				return (1);
			if (ft_atoi(av[i]) == -1)
				return (1);
			if (i != 1 && i != 5 && ft_atoi(av[i]) == 0)
				return (1);
			i++;
		}
	}
	else
		return (1);
	return (0);
}
