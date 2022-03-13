# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arudy <arudy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 09:49:31 by arudy             #+#    #+#              #
#    Updated: 2022/03/13 16:16:49 by arudy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = $(addprefix srcs/, main.c parsing/check_args.c \
		parsing/init_data.c utils/ft_putstr_fd.c \
		utils/ft_strlen.c utils/ft_error.c routine/routine.c)

OBJS = ${SRCS:.c=.o}

NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread

RM = rm -f

all: ${NAME}

${NAME}:	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
