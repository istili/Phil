# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: istili <istili@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 09:53:55 by istili            #+#    #+#              #
#    Updated: 2024/09/11 10:56:31 by istili           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo


CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -g3 #-fsanitize=address -ggdb3

RM				=	rm -rf

HEADER			=	philo.h


FILE			=	watcher.c split.c libc.c atoi.c destroy.c parsing.c main.c philo.c helpers.c routine.c \


OBJS			=	$(FILE:.c=.o)


all : $(NAME)

$(NAME) : $(OBJS)
	$(CC)  $(OBJS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -pthread


clean :
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
