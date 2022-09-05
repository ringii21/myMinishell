# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abonard <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:12:51 by abonard           #+#    #+#              #
#    Updated: 2022/02/08 17:28:38 by abonard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-*-Makefile-*-

SRCS		= 		ft_isalpha.c\
					ft_isdigit.c\
					ft_isalnum.c\
					ft_isascii.c\
					ft_isprint.c\
					ft_strlen.c\
					ft_memset.c\
					ft_bzero.c\
					ft_memcpy.c\
					ft_memmove.c\
					ft_strlcpy.c\
					ft_strlcat.c\
					ft_toupper.c\
					ft_tolower.c\
					ft_strchr.c\
					ft_strrchr.c\
					ft_strncmp.c\
					ft_memchr.c\
					ft_memcmp.c\
					ft_strnstr.c\
					ft_atoi.c\
					ft_calloc.c\
					ft_strdup.c\
					ft_substr.c\
					ft_strjoin.c\
					ft_strtrim.c\
					ft_split.c\
					ft_itoa.c\
					ft_putchar_fd.c\
					ft_putstr_fd.c\
					ft_putnbr_fd.c\
					ft_putendl_fd.c\
					ft_strmapi.c\
					ft_initialise_tab.c \
					ft_len.c \
					ft_len_hexa.c \
					ft_number.c \
					ft_parsing.c \
					ft_pfmt.c \
					ft_printf.c \
					ft_putnbr_base.c \
					ft_strcpy.c \
					ft_string.c \
					ft_strlen_custom.c \
					ft_xfmt.c \
					ft_striteri.c\
					ft_strcmp.c \
					ft_gnl.c \
					ft_tablen.c \
					ft_free_stab.c

HEAD		=		libft.h \
					ft_struct.h \
					ft_printf.h

HEAD_DIR 	= 		./
OBJS		= ${SRCS:.c=.o}

NAME		= libft.a

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

.c.o:
			@${CC} ${CFLAGS} -I ${HEAD_DIR} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar -rc libft.a ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all	clean	fclean re
