/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 01:49:19 by istili            #+#    #+#             */
/*   Updated: 2024/08/26 06:35:17 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef philo_H	
# define philo_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *line, char *bufr);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		args(char *s);
void	free_array(char **arr);
int		is_full_space(char *str);
int		ft_puterror(void);
int		ft_strcmp(const	char *s1, const	char *s2);
int		ft_atoi(const char *str);

#endif