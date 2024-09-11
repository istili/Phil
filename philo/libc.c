/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:16:42 by istili            #+#    #+#             */
/*   Updated: 2024/09/11 09:04:24 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	x;
	size_t	slen;

	x = 0;
	slen = ft_strlen(src);
	if (dstsize != 0)
	{
		while (src[x] && x < (dstsize - 1))
		{
			dst[x] = src[x];
			x++;
		}
		dst[x] = 0;
	}
	return (slen);
}

char	*ft_strjoin(char *line, char *bufr)
{
	char	*s;
	size_t	i;
	size_t	j;

	s = (char *)malloc(ft_strlen(line) + ft_strlen(bufr) + 2);
	if (!s)
		return ((free(line)), NULL);
	i = 0;
	while (line != NULL && line[i] != '\0')
	{
		s[i] = line[i];
		i++;
	}
	j = -1;
	s[i++] = ' ';
	while (bufr != 0 && bufr[++j] != '\0')
		s[i + j] = bufr[j];
	s[i + j] = '\0';
	if (line)
		free(line);
	return (s);
}

int	ft_strcmp(const	char *s1, const	char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(b + i) = (unsigned char)c;
		i++;
	}
	return (b);
}
