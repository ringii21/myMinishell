# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/07 19:14:12 by seozcan           #+#    #+#              #
#    Updated: 2022/09/19 19:47:12 by seozcan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::TARGET::

NAME	:= libft.a

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::SOURCES::

SDIR	:= srcs

SRCS	:= 			ft_isalpha.c\
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

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::OBJECTS::

ODIR	:= objs

OBJS	=  $(addprefix $(ODIR)/, $(SRCS:.c=.o))

DEPS	= $(OBJS:.o=.d)

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::COMPILERS::

CC		:= clang

WFLAGS	:= -MMD -Wall -Wextra -Werror 

WCONV 	:= -Wconversion

GFLAG	:=  -g3

SANFLAG	:= -fsanitize=address

AR		:= ar

ARFLAGS	:= rcs

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::HEADERS::

IDIR	:= inc

INC		:= libft.h

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::COLORS::

NO_COLOR		=	\033[m

BLACK			=	\033[0;30m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
ORANGE 		 	=	\033[0;33m
BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
CYAN			=	\033[0;36m
WHITE			= 	\033[0;37m

# High Intensty
HIGREEN			=	\033[0;92m
HIORANGE	 	=	\033[0;93m
HIPURPLE		=	\033[0;95m

# Bold
BORANGE 		=	\033[1;33m
BBLUE			=	\033[1;34m
BPURPLE			=	\033[1;35m
BCYAN			=	\033[1;36m

# Bold High Intensity
BHIGREEN		=	\033[1;92m
BHIORANGE	 	=	\033[1;93m
BHIPURPLE		=	\033[1;95m

# Italic
ICYAN			=	\033[3;36m

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::RULES::

vpath %.c $(SDIR)
vpath %.o $(ODIR)

all:			header message $(NAME)

$(ODIR)/%.o:	%.c
	@$(CC) $(WFLAGS) -I $(IDIR) -c $< -o $@
	@echo "$(HIGREEN)libft compilation:\t\t\t\t\t[OK]$(NO_COLOR)"

$(NAME):		$(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo "$(HIGREEN)$(NAME):\t\t\t\t\t\t[OK]$(NO_COLOR)"

$(OBJS):		| $(ODIR)

$(ODIR):
	@mkdir -p $(ODIR)
	@echo "$(BHIGREEN)libft objs folder:\t\t\t\t\t[OK]$(NO_COLOR)"

clean:
ifneq ($(wildcard ./$(ODIR)),)
	@rm -rf $(ODIR)
	@echo "$(HIORANGE)libft objs folder:\t\t\t\t\t[RM]$(NO_COLOR)"
else
	@rm -f $(wildcard %.o)
	@echo "$(HIORANGE)libft obj files:\t\t\t\t\t[RM]$(NO_COLOR)"
endif

fclean:		clean
	@rm -f $(NAME)
	@echo "$(HIORANGE)$(NAME):\t\t\t\t\t\t[RM]$(NO_COLOR)"

header:
	@echo "\n$(BHIPURPLE):::::::::::::::::::::::::::::::::::::::::::::::::::::LIBFT::\n$(NO_COLOR)"

message:
	@make -q $(NAME) && echo "$(BHIGREEN)All files are already up to date\n$(NO_COLOR)" || true

re:		fclean all

-include $(DEPS)

.PHONY:	all clean fclean re