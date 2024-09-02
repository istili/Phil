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
# include <sys/time.h>

// typedef pthread_forks_t forks_t;

typedef struct s_philo
{
    struct s_main   *ptr; 
    int             id;
    pthread_t       th;
    int             l_fork;
    int             r_fork;
    long            last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	meals_mutex;
	int				is_full;
}   t_philo;

typedef struct s_main
{
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    t_philo         *arr;
    int             n_philo;
    int             eat;
    int             die;
    int             sleep;
	int				max_meals;
    int             start;
    long            start_time;
    pthread_mutex_t int_mutex;
}   t_main;


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
void	*ft_memset(void *b, int c, size_t len);

#endif