# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 16:41:59 by tpotilli          #+#    #+#              #
#    Updated: 2024/01/18 14:35:42 by tpotilli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	Pipex

OBJS_PATH	= objs/

SRCS	=	srcs/main.c\
			srcs/pipex.c\
			srcs/ft_create_and_verify.c\
			srcs/ft_child_process.c\
			srcs/execute.c\
			libft/ft_split.c\
			libft/ft_strlen.c\
			libft/ft_strnstr.c\
			libft/ft_substr.c\
			libft/ft_strdup.c\
			libft/ft_strjoin.c\
			libft/ft_strncmp.c\
			libft/ft_is_alpha.c\

OBJS = $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra -g3 -Iincludes

all : ${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			rm -rf ${OBJS}

fclean:		clean
			rm -rf ${NAME}

re:			fclean all

.PHONY:	all clean fclean re

${OBJS_PATH}%.o: %.c
		@mkdir -p $(@D)
		${CC} ${CFLAGS} -c $< -o $@