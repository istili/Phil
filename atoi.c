/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:05:34 by istili            #+#    #+#             */
/*   Updated: 2024/08/26 06:34:07 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	check_sign(const char *str, int i)
{
	int	sign;

	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
	}
	return (sign);
}

static void	spaces(const char **str)
{
	while (**str == '\t' || **str == '\f' || **str == '\r'
		|| **str == '\v' || **str == '\n' || **str == ' ')
		(*str)++;
}

int	ft_atoi(const char *str)
{
	long	nb;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	spaces(&str);
	sign = check_sign(str, i);
	if (str[i] == '-' || str[i] == '+')
		i++;
	nb = 0;
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + str[i++] - '0';
		if ((nb > INT_MAX && sign == 1)
			|| (nb > -(long)(INT_MIN) && sign == -1))
			ft_puterror();
	}
	return (nb * sign);
}
