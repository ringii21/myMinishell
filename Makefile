# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abonard <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/08 19:48:37 by abonard           #+#    #+#              #
#    Updated: 2022/02/08 20:28:17 by abonard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NC = \033[0m
RED = \033[0;91m
ORANGE = \033[93m
GREEN = \033[0;92m
PURPLE = \033[0;95m
BLUE = \033[0;34m
BOLD = \033[1m

SRCS		=	./srcs/main.c \
				./srcs/ft_env_utils.c \
				./srcs/ft_signals.c \
				./srcs/buildins/ft_env.c \
				./srcs/buildins/ft_pwd.c \
				./srcs/buildins/ft_exit.c

INCLUDES	=	./libft/inc/libft.h \
				./inc/minishell.h

HEAD		= ./inc/

LIBFT		= ./libft/libft.a

LIB_DIR		= ./libft/

NAME		= minishell

CC			= gcc

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -g


.c.o:
		@${CC} ${CFLAGS} -I${HEAD} -c $< -o ${<:.c=.o}
		@echo "${GREEN}[ OK ]	${ORANGE}${<:.s=.o}${NC}"

all:		${NAME}

${NAME}:	${OBJS}
			@make -C ${LIB_DIR}
			@echo "${GREEN}\nlibft.a		has been created"
			@${CC} ${CFLAGS} -I${HEAD} -o ${NAME} $(OBJS) ${LIBFT}
			@echo "minishell		has been created\n${NC}"

clean:
			@make -C $(LIB_DIR) clean
			@${RM} ${OBJS}
			@echo "${GREEN}[ OK ]${RED}	*.o files	deleted${NC}"

fclean:		clean
			@make -C $(LIB_DIR) fclean
			@echo "${GREEN}[ OK ]${RED}	libft.a		deleted${NC}"
			@${RM} ${NAME}
			@echo "${GREEN}[ OK ]${RED}everything	deleted${NC}"

re :		fclean all

.PHONY:		all	clean	fclean re
